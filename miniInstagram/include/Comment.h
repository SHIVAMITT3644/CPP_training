#ifndef COMMENT_H
#define COMMENT_H

#include <string>

class Comment
{
private:
    std::string commentId;
    std::string commentedByUsername;
    std::string commentedByName;
    std::string text;

public:
    Comment(const std::string& commentId,
            const std::string& commentedByUsername,
            const std::string& commentedByName,
            const std::string& text);

    std::string getCommentId() const;
    std::string getCommentedByUsername() const;
    std::string getCommentedByName() const;
    std::string getText() const;
};

#endif
