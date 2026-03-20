#ifndef IFILEPOSTSTORAGE_H
#define IFILEPOSTSTORAGE_H

#include <string>
#include <vector>
#include <optional>
#include "Post.h"

class IFilePostStorage
{
public:
    virtual ~IFilePostStorage() = default;

    virtual bool addPost(const Post& post) = 0;
    virtual bool updatePost(const Post& post) = 0;
    virtual bool deletePost(const std::string& postId, const std::string& authorUsername) = 0;

    virtual std::optional<Post> getPostById(const std::string& postId,
                                            const std::string& authorUsername) const = 0;

    virtual std::vector<Post> getPostsByUsername(const std::string& username) const = 0;
    virtual std::vector<Post> getAllPosts() const = 0;
};

#endif
