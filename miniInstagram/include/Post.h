#ifndef POST_H
#define POST_H

#include <string>
#include <map>
#include <vector>
#include "Comment.h"

class Post
{
private:
    std::string postId;
    std::string authorUsername;
    std::string authorName;
    std::string content;
    long long createdAt;

    std::map<std::string, std::string> likedByUsers;
    std::vector<Comment> comments;

public:
    Post(const std::string& postId,
         const std::string& authorUsername,
         const std::string& authorName,
         const std::string& content,
         long long createdAt);

    std::string getPostId() const;
    std::string getAuthorUsername() const;
    std::string getAuthorName() const;
    std::string getContent() const;
    long long getCreatedAt() const;

    bool addLike(const std::string& username, const std::string& fullName);
    bool removeLike(const std::string& username);
    bool hasLiked(const std::string& username) const;

    size_t getLikeCount() const;
    std::map<std::string, std::string> getLikedUsers() const;

    bool addComment(const Comment& comment);
    bool editComment(int commentIndex, const std::string& updatedText);
    bool deleteComment(int commentIndex);

    std::vector<Comment> getComments() const;
};

#endif
