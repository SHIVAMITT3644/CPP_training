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

bool PostManager::updatePostContent(const std::string& postId,
                                    const std::string& authorUsername,
                                    const std::string& updatedContent)
{
    std::optional<Post> post = postStorage.getPostById(postId, authorUsername);

    if (!post.has_value())
    {
        return false;
    }

    Post updatedPost(
        post->getPostId(),
        post->getAuthorUsername(),
        post->getAuthorName(),
        updatedContent,
        post->getCreatedAt()
    );

    std::map<std::string, std::string> likedUsers = post->getLikedUsers();
    for (const auto& likedUser : likedUsers)
    {
        updatedPost.addLike(likedUser.first, likedUser.second);
    }

    std::vector<Comment> comments = post->getComments();
    for (const Comment& comment : comments)
    {
        updatedPost.addComment(comment);
    }

    return postStorage.updatePost(updatedPost);
}

std::optional<Post> PostManager::getPostById(const std::string& postId,
                                             const std::string& authorUsername) const
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

bool PostManager::editCommentInPost(const std::string& postId,
                                    const std::string& authorUsername,
                                    int commentIndex,
                                    const std::string& updatedText)
{
    std::optional<Post> post = postStorage.getPostById(postId, authorUsername);

    if (!post.has_value())
    {
        return false;
    }

    if (!post->editComment(commentIndex, updatedText))
    {
        return false;
    }

    return postStorage.updatePost(post.value());
}

bool PostManager::deleteCommentFromPost(const std::string& postId,
                                        const std::string& authorUsername,
                                        int commentIndex)
{
    std::optional<Post> post = postStorage.getPostById(postId, authorUsername);

    if (!post.has_value())
    {
        return false;
    }

    if (!post->deleteComment(commentIndex))
    {
        return false;
    }

    return postStorage.updatePost(post.value());
}
