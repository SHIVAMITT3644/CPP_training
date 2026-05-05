#include "FilePostStorage.h"

#include <filesystem>
#include <fstream>
#include <algorithm>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

namespace
{
    json convertCommentToJson(const Comment& comment)
    {
        json commentJson;
        commentJson["commentedByUsername"] = comment.getCommentedByUsername();
        commentJson["commentedByName"] = comment.getCommentedByName();
        commentJson["text"] = comment.getText();
        return commentJson;
    }

    Comment convertJsonToComment(const json& commentJson)
    {
        return Comment(
            commentJson.value("commentedByUsername", ""),
            commentJson.value("commentedByName", ""),
            commentJson.value("text", "")
        );
    }

    json convertPostToJson(const Post& post)
    {
        json postJson;
        postJson["username"] = post.getAuthorUsername();
        postJson["authorName"] = post.getAuthorName();
        postJson["postId"] = post.getPostId();
        postJson["content"] = post.getContent();
        postJson["createdAt"] = post.getCreatedAt();

        postJson["likedByUsers"] = json::array();
        std::map<std::string, std::string> likedUsers = post.getLikedUsers();

        for (const auto& likedUser : likedUsers)
        {
            json likedUserJson;
            likedUserJson["username"] = likedUser.first;
            likedUserJson["name"] = likedUser.second;
            postJson["likedByUsers"].push_back(likedUserJson);
        }

        postJson["comments"] = json::array();
        for (const Comment& comment : post.getComments())
        {
            postJson["comments"].push_back(convertCommentToJson(comment));
        }

        return postJson;
    }

    Post convertJsonToPost(const json& postJson)
    {
        Post post(
            postJson.value("postId", ""),
            postJson.value("username", ""),
            postJson.value("authorName", ""),
            postJson.value("content", ""),
            postJson.value("createdAt", 0LL)
        );

        if (postJson.contains("likedByUsers") && postJson["likedByUsers"].is_array())
        {
            for (const auto& likedUserJson : postJson["likedByUsers"])
            {
                std::string username = likedUserJson.value("username", "");
                std::string name = likedUserJson.value("name", "");

                if (!username.empty())
                {
                    post.addLike(username, name);
                }
            }
        }

        if (postJson.contains("comments") && postJson["comments"].is_array())
        {
            for (const auto& commentJson : postJson["comments"])
            {
                post.addComment(convertJsonToComment(commentJson));
            }
        }

        return post;
    }

    void sortPostsLatestToOldest(std::vector<Post>& posts)
    {
        std::sort(posts.begin(), posts.end(),
                  [](const Post& firstPost, const Post& secondPost)
                  {
                      return firstPost.getCreatedAt() > secondPost.getCreatedAt();
                  });
    }
}

FilePostStorage::FilePostStorage(const std::string& postDirectoryPath)
    : postDirectoryPath(postDirectoryPath)
{
    ensurePostDirectoryExists();
}

std::string FilePostStorage::getUserPostFilePath(const std::string& username) const
{
    return postDirectoryPath + "/" + username + ".json";
}

bool FilePostStorage::ensurePostDirectoryExists() const
{
    try
    {
        if (!std::filesystem::exists(postDirectoryPath))
        {
            return std::filesystem::create_directories(postDirectoryPath);
        }

        return true;
    }
    catch (...)
    {
        return false;
    }
}

std::vector<Post> FilePostStorage::loadPostsFromFile(const std::string& username) const
{
    std::vector<Post> posts;
    std::string filePath = getUserPostFilePath(username);

    if (!std::filesystem::exists(filePath))
    {
        return posts;
    }

    std::ifstream inputFile(filePath);

    if (!inputFile.is_open())
    {
        return posts;
    }

    try
    {
        json postsJson;
        inputFile >> postsJson;

        if (!postsJson.is_array())
        {
            return posts;
        }

        for (const auto& postJson : postsJson)
        {
            Post post = convertJsonToPost(postJson);

            if (!post.getPostId().empty())
            {
                posts.push_back(post);
            }
        }

        sortPostsLatestToOldest(posts);
    }
    catch (...)
    {
        return {};
    }

    return posts;
}

bool FilePostStorage::savePostsToFile(const std::string& username,
                                      const std::vector<Post>& posts) const
{
    if (!ensurePostDirectoryExists())
    {
        return false;
    }

    std::ofstream outputFile(getUserPostFilePath(username));

    if (!outputFile.is_open())
    {
        return false;
    }

    json postsJson = json::array();

    for (const Post& post : posts)
    {
        postsJson.push_back(convertPostToJson(post));
    }

    outputFile << postsJson.dump(4);
    return outputFile.good();
}

bool FilePostStorage::addPost(const Post& post)
{
    std::vector<Post> posts = loadPostsFromFile(post.getAuthorUsername());

    for (const Post& existingPost : posts)
    {
        if (existingPost.getPostId() == post.getPostId())
        {
            return false;
        }
    }

    posts.push_back(post);
    sortPostsLatestToOldest(posts);

    return savePostsToFile(post.getAuthorUsername(), posts);
}

bool FilePostStorage::updatePost(const Post& post)
{
    std::vector<Post> posts = loadPostsFromFile(post.getAuthorUsername());

    for (Post& existingPost : posts)
    {
        if (existingPost.getPostId() == post.getPostId())
        {
            existingPost = post;
            sortPostsLatestToOldest(posts);
            return savePostsToFile(post.getAuthorUsername(), posts);
        }
    }

    return false;
}

bool FilePostStorage::deletePost(const std::string& postId,
                                 const std::string& authorUsername)
{
    std::vector<Post> posts = loadPostsFromFile(authorUsername);
    std::vector<Post> updatedPosts;

    bool isDeleted = false;

    for (const Post& post : posts)
    {
        if (post.getPostId() == postId)
        {
            isDeleted = true;
            continue;
        }

        updatedPosts.push_back(post);
    }

    if (!isDeleted)
    {
        return false;
    }

    sortPostsLatestToOldest(updatedPosts);

    return savePostsToFile(authorUsername, updatedPosts);
}

std::optional<Post> FilePostStorage::getPostById(const std::string& postId,
                                                 const std::string& authorUsername) const
{
    std::vector<Post> posts = loadPostsFromFile(authorUsername);

    for (const Post& post : posts)
    {
        if (post.getPostId() == postId)
        {
            return post;
        }
    }

    return std::nullopt;
}

std::vector<Post> FilePostStorage::getPostsByUsername(const std::string& username) const
{
    std::vector<Post> posts = loadPostsFromFile(username);
    sortPostsLatestToOldest(posts);
    return posts;
}

std::vector<Post> FilePostStorage::getAllPosts() const
{
    std::vector<Post> allPosts;

    if (!std::filesystem::exists(postDirectoryPath))
    {
        return allPosts;
    }

    try
    {
        for (const auto& entry : std::filesystem::directory_iterator(postDirectoryPath))
        {
            if (!entry.is_regular_file())
            {
                continue;
            }

            if (entry.path().extension() != ".json")
            {
                continue;
            }

            std::ifstream inputFile(entry.path());

            if (!inputFile.is_open())
            {
                continue;
            }

            json postsJson;
            inputFile >> postsJson;

            if (!postsJson.is_array())
            {
                continue;
            }

            for (const auto& postJson : postsJson)
            {
                Post post = convertJsonToPost(postJson);

                if (!post.getPostId().empty())
                {
                    allPosts.push_back(post);
                }
            }
        }

        sortPostsLatestToOldest(allPosts);
    }
    catch (...)
    {
        return allPosts;
    }

    return allPosts;
}
