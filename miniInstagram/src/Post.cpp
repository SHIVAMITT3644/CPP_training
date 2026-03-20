#include "Post.h"

Post::Post(const std::string& postId,
           const std::string& authorUsername,
           const std::string& authorName,
           const std::string& content)
    : postId(postId),
      authorUsername(authorUsername),
      authorName(authorName),
      content(content)
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

std::vector<Comment> Post::getComments() const
{
    return comments;
}
