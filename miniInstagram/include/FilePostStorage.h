#ifndef FILEPOSTSTORAGE_H
#define FILEPOSTSTORAGE_H

#include <string>
#include <vector>
#include <optional>
#include "IFilePostStorage.h"
#include "Post.h"

class FilePostStorage : public IFilePostStorage
{
private:
    std::string postDirectoryPath;

    std::string getPostFilePath(const std::string& authorUsername, const std::string& postId) const;

    bool ensurePostDirectoryExists() const;

public:
    FilePostStorage(const std::string& postDirectoryPath);

    bool addPost(const Post& post) override;
    bool updatePost(const Post& post) override;
    bool deletePost(const std::string& postId, const std::string& authorUsername) override;

    std::optional<Post> getPostById(const std::string& postId, const std::string& authorUsername) const override;

    std::vector<Post> getPostsByUsername(const std::string& username) const override;
    std::vector<Post> getAllPosts() const override;
};

#endif
