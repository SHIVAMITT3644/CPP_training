#include "Post.h"

Post::Post(const std::string& postId,
           const std::string& authorUsername,
           const std::string& authorName,
           const std::string& content,
           long long createdAt)
    : postId(postId),
      authorUsername(authorUsername),
      authorName(authorName),
      content(content),
      createdAt(createdAt)
{
}

std::string Post::getPostId() const
{
    return postId;
}

std::string Post::getAuthorUsername() const
{
    return authorUsername;
}

std::string Post::getAuthorName() const
{
    return authorName;
}

std::string Post::getContent() const
{
    return content;
}

long long Post::getCreatedAt() const
{
    return createdAt;
}

bool Post::addLike(const std::string& username, const std::string& fullName)
{
    return likedByUsers.insert({username, fullName}).second;
}

bool Post::removeLike(const std::string& username)
{
    return likedByUsers.erase(username) > 0;
}

bool Post::hasLiked(const std::string& username) const
{
    return likedByUsers.find(username) != likedByUsers.end();
}

size_t Post::getLikeCount() const
{
    return likedByUsers.size();
}

std::map<std::string, std::string> Post::getLikedUsers() const
{
    return likedByUsers;
}

bool Post::addComment(const Comment& comment)
{
    comments.push_back(comment);
    return true;
}

bool Post::editComment(int commentIndex, const std::string& updatedText)
{
    if (commentIndex < 0 || commentIndex >= static_cast<int>(comments.size()))
    {
        return false;
    }

    Comment existingComment = comments[commentIndex];

    comments[commentIndex] = Comment(
        existingComment.getCommentedByUsername(),
        existingComment.getCommentedByName(),
        updatedText
    );

    return true;
}

bool Post::deleteComment(int commentIndex)
{
    if (commentIndex < 0 || commentIndex >= static_cast<int>(comments.size()))
    {
        return false;
    }

    comments.erase(comments.begin() + commentIndex);
    return true;
}

std::vector<Comment> Post::getComments() const
{
    return comments;
}
