#include "Comment.h"

Comment::Comment(const std::string& commentId,
                 const std::string& commentedByUsername,
                 const std::string& commentedByName,
                 const std::string& text)
    : commentId(commentId),
      commentedByUsername(commentedByUsername),
      commentedByName(commentedByName),
      text(text)
{
}

std::string Comment::getCommentId() const
{
    return commentId;
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
