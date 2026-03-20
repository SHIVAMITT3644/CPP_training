#include "PostManager.h"

PostManager::PostManager(IFilePostStorage& postStorage)
    : postStorage(postStorage)
{
}

bool PostManager::createPost(const Post& post)
{
    return postStorage.addPost(post);
}

bool PostManager::deletePost(const std::string& postId, const std::string& authorUsername)
{
    return postStorage.deletePost(postId, authorUsername);
}

std::optional<Post> PostManager::getPostById(const std::string& postId, const std::string& authorUsername) const
{
    return postStorage.getPostById(postId, authorUsername);
}

std::vector<Post> PostManager::getPostsByUsername(const std::string& username) const
{
    return postStorage.getPostsByUsername(username);
}

std::vector<Post> PostManager::getAllPosts() const
{
    return postStorage.getAllPosts();
}

bool PostManager::likePost(const std::string& postId,
                           const std::string& authorUsername,
                           const std::string& likedByUsername,
                           const std::string& likedByName)
{
    std::optional<Post> post = postStorage.getPostById(postId, authorUsername);

    if (!post.has_value())
    {
        return false;
    }

    if (!post->addLike(likedByUsername, likedByName))
    {
        return false;
    }

    return postStorage.updatePost(post.value());
}

bool PostManager::unlikePost(const std::string& postId,
                             const std::string& authorUsername,
                             const std::string& likedByUsername)
{
    std::optional<Post> post = postStorage.getPostById(postId, authorUsername);

    if (!post.has_value())
    {
        return false;
    }

    if (!post->removeLike(likedByUsername))
    {
        return false;
    }

    return postStorage.updatePost(post.value());
}

bool PostManager::addCommentToPost(const std::string& postId,
                                   const std::string& authorUsername,
                                   const Comment& comment)
{
    std::optional<Post> post = postStorage.getPostById(postId, authorUsername);

    if (!post.has_value())
    {
        return false;
    }

    if (!post->addComment(comment))
    {
        return false;
    }

    return postStorage.updatePost(post.value());
}
