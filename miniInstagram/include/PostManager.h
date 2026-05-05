#ifndef POSTMANAGER_H
#define POSTMANAGER_H

#include <string>
#include <vector>
#include <optional>
#include "IFilePostStorage.h"
#include "Post.h"
#include "Comment.h"

class PostManager
{
private:
    IFilePostStorage& postStorage;

public:
    explicit PostManager(IFilePostStorage& postStorage);

    bool createPost(const Post& post);
    bool deletePost(const std::string& postId, const std::string& authorUsername);

    bool updatePostContent(const std::string& postId,
                           const std::string& authorUsername,
                           const std::string& updatedContent);

    std::optional<Post> getPostById(const std::string& postId,
                                    const std::string& authorUsername) const;

    std::vector<Post> getPostsByUsername(const std::string& username) const;
    std::vector<Post> getAllPosts() const;

    bool likePost(const std::string& postId,
                  const std::string& authorUsername,
                  const std::string& likedByUsername,
                  const std::string& likedByName);

    bool unlikePost(const std::string& postId,
                    const std::string& authorUsername,
                    const std::string& likedByUsername);

    bool addCommentToPost(const std::string& postId,
                          const std::string& authorUsername,
                          const Comment& comment);

    bool editCommentInPost(const std::string& postId,
                           const std::string& authorUsername,
                           int commentIndex,
                           const std::string& updatedText);

    bool deleteCommentFromPost(const std::string& postId,
                               const std::string& authorUsername,
                               int commentIndex);
};

#endif
