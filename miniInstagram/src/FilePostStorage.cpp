#include "FilePostStorage.h"

#include <filesystem>
#include <fstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

namespace
{
    json convertCommentToJson(const Comment& comment)
    {
        json commentJson;
        commentJson["commentId"] = comment.getCommentId();
        commentJson["commentedByUsername"] = comment.getCommentedByUsername();
        commentJson["commentedByName"] = comment.getCommentedByName();
        commentJson["text"] = comment.getText();
        return commentJson;
    }

    Comment convertJsonToComment(const json& commentJson)
    {
        return Comment(
            commentJson.value("commentId", ""),
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
            postJson.value("content", "")
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
}

FilePostStorage::FilePostStorage(const std::string& postDirectoryPath)
    : postDirectoryPath(postDirectoryPath)
{
    ensurePostDirectoryExists();
}

std::string FilePostStorage::getPostFilePath(const std::string& authorUsername,
                                             const std::string& postId) const
{
    return postDirectoryPath + "/" + authorUsername + "_" + postId + ".json";
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

bool FilePostStorage::addPost(const Post& post)
{
    if (!ensurePostDirectoryExists())
    {
        return false;
    }

    std::string filePath = getPostFilePath(post.getAuthorUsername(), post.getPostId());

    if (std::filesystem::exists(filePath))
    {
        return false;
    }

    std::ofstream outputFile(filePath);

    if (!outputFile.is_open())
    {
        return false;
    }

    outputFile << convertPostToJson(post).dump(4);
    return outputFile.good();
}

bool FilePostStorage::updatePost(const Post& post)
{
    if (!ensurePostDirectoryExists())
    {
        return false;
    }

    std::ofstream outputFile(getPostFilePath(post.getAuthorUsername(), post.getPostId()));

    if (!outputFile.is_open())
    {
        return false;
    }

    outputFile << convertPostToJson(post).dump(4);
    return outputFile.good();
}

bool FilePostStorage::deletePost(const std::string& postId,
                                 const std::string& authorUsername)
{
    try
    {
        std::string filePath = getPostFilePath(authorUsername, postId);

        if (!std::filesystem::exists(filePath))
        {
            return false;
        }

        return std::filesystem::remove(filePath);
    }
    catch (...)
    {
        return false;
    }
}

std::optional<Post> FilePostStorage::getPostById(const std::string& postId,
                                                 const std::string& authorUsername) const
{
    std::ifstream inputFile(getPostFilePath(authorUsername, postId));

    if (!inputFile.is_open())
    {
        return std::nullopt;
    }

    try
    {
        json postJson;
        inputFile >> postJson;

        Post post = convertJsonToPost(postJson);

        if (post.getPostId().empty() || post.getAuthorUsername().empty())
        {
            return std::nullopt;
        }

        return post;
    }
    catch (...)
    {
        return std::nullopt;
    }
}

std::vector<Post> FilePostStorage::getPostsByUsername(const std::string& username) const
{
    std::vector<Post> posts;

    if (!std::filesystem::exists(postDirectoryPath))
    {
        return posts;
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

            json postJson;
            inputFile >> postJson;

            if (postJson.value("username", "") != username)
            {
                continue;
            }

            Post post = convertJsonToPost(postJson);

            if (!post.getPostId().empty())
            {
                posts.push_back(post);
            }
        }
    }
    catch (...)
    {
        return posts;
    }

    return posts;
}

std::vector<Post> FilePostStorage::getAllPosts() const
{
    std::vector<Post> posts;

    if (!std::filesystem::exists(postDirectoryPath))
    {
        return posts;
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

            json postJson;
            inputFile >> postJson;

            Post post = convertJsonToPost(postJson);

            if (!post.getPostId().empty())
            {
                posts.push_back(post);
            }
        }
    }
    catch (...)
    {
        return posts;
    }

    return posts;
}
