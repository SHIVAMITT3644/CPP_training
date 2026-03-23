#include "Comment.h"

Comment::Comment(const std::string& commentedByUsername,
                 const std::string& commentedByName,
                 const std::string& text)
    : commentedByUsername(commentedByUsername),
      commentedByName(commentedByName),
      text(text)
{
}

std::string Comment::getCommentedByUsername() const
{
    return commentedByUsername;
}

std::string Comment::getCommentedByName() const
{
    return commentedByName;
}

std::string Comment::getText() const
{
    return text;
}
