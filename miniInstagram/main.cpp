#include <iostream>
#include <string>
#include <vector>
#include <optional>
#include <map>

#include "Constants.h"
#include "Input.h"
#include "User.h"
#include "Comment.h"
#include "Post.h"
#include "ICryptoService.h"
#include "CryptoService.h"
#include "IFileUserStorage.h"
#include "FileUserStorage.h"
#include "IFilePostStorage.h"
#include "FilePostStorage.h"
#include "UserManager.h"
#include "AuthManager.h"
#include "PostManager.h"

namespace
{
    int generatePostNumber()
    {
        static int postCounter = 1;
        return postCounter++;
    }

    int generateCommentNumber()
    {
        static int commentCounter = 1;
        return commentCounter++;
    }

    std::string generatePostId()
    {
        return "post" + std::to_string(generatePostNumber());
    }

    std::string generateCommentId()
    {
        return "comment" + std::to_string(generateCommentNumber());
    }

    void printMainMenu()
    {
        std::cout << R"(
============================
1. Login
2. Signup
3. Exit
============================
)";
    }

    void printUserMenu()
    {
        std::cout << R"(
============================
1. Create Post
2. View All Posts
3. View My Posts
4. Like Post
5. Unlike Post
6. Add Comment
7. Logout
============================
)";
    }

    void displaySinglePost(const Post& post)
    {
        std::cout << "\n----------------------------------\n";
        std::cout << "Post ID      : " << post.getPostId() << "\n";
        std::cout << "Author       : " << post.getAuthorName() << "\n";
        std::cout << "Content      : " << post.getContent() << "\n";
        std::cout << "Like Count   : " << post.getLikeCount() << "\n";

        std::map<std::string, std::string> likedUsers = post.getLikedUsers();

        std::cout << "Liked By     : ";
        if (likedUsers.empty())
        {
            std::cout << "No likes yet";
        }
        else
        {
            for (const auto& likedUser : likedUsers)
            {
                std::cout << likedUser.second << " ";
            }
        }
        std::cout << "\n";

        std::vector<Comment> comments = post.getComments();
        std::cout << "Comments     : ";
        if (comments.empty())
        {
            std::cout << "No comments yet\n";
        }
        else
        {
            std::cout << "\n";
            for (const Comment& comment : comments)
            {
                std::cout << "  [" << comment.getCommentId() << "] "
                          << comment.getCommentedByName()
                          << " : " << comment.getText() << "\n";
            }
        }

        std::cout << "----------------------------------\n";
    }

    void displayPosts(const std::vector<Post>& posts)
    {
        if (posts.empty())
        {
            std::cout << "\nNo posts found.\n";
            return;
        }

        for (const Post& post : posts)
        {
            displaySinglePost(post);
        }
    }

    void handleSignUp(AuthManager& authManager)
    {
        std::string username;
        std::string name;
        std::string password;
        std::string bio;

        readCompleteLineInput(std::cin, name, "Enter full name: ");
        readCompleteLineInput(std::cin, username, USERNAME_INPUT_PROMPT);
        password = readHiddenPassword(PASSWORD_INPUT_PROMPT);
        readCompleteLineInput(std::cin, bio, "Enter bio: ");

        if (username.length() < 5)
        {
            std::cout << USERNAME_INPUT_ERROR_MESSAGE;
            return;
        }

        if (password.length() < 5)
        {
            std::cout << PASSWORD_INPUT_ERROR_MESSAGE;
            return;
        }

        bool isSignUpSuccessful = authManager.signUp(username, name, password, bio);

        if (isSignUpSuccessful)
        {
            std::cout << ACCOUNT_CREATED_MESSAGE << username << "\n";
        }
        else
        {
            std::cout << CREATE_ACCOUT_USER_EXIST_ERROR_MESSAGE;
        }
    }

    bool handleLogin(AuthManager& authManager)
    {
        std::string username;
        std::string password;

        readCompleteLineInput(std::cin, username, USERNAME_INPUT_PROMPT);
        password = readHiddenPassword(PASSWORD_INPUT_PROMPT);

        bool isLoginSuccessful = authManager.signIn(username, password);

        if (!isLoginSuccessful)
        {
            std::cout << INVALID_PASSWORD_ERROR_MESSAGE;
            return false;
        }

        std::cout << "\nLogin successful.\n";
        return true;
    }

    void handleCreatePost(AuthManager& authManager, PostManager& postManager)
    {
        std::optional<User> loggedInUser = authManager.getLoggedInUser();

        if (!loggedInUser.has_value())
        {
            std::cout << "\nNo user is logged in.\n";
            return;
        }

        std::string content;
        readCompleteLineInput(std::cin, content, "Enter post content: ");

        std::string postId = generatePostId();

        Post post(postId,
                  loggedInUser->getUserName(),
                  loggedInUser->getName(),
                  content);

        if (postManager.createPost(post))
        {
            std::cout << "\nPost created successfully.\n";
            std::cout << "Generated Post ID: " << postId << "\n";
        }
        else
        {
            std::cout << TECHNICAL_ERROR_MESSAGE;
        }
    }

    void handleViewAllPosts(PostManager& postManager)
    {
        std::vector<Post> posts = postManager.getAllPosts();
        displayPosts(posts);
    }

    void handleViewMyPosts(AuthManager& authManager, PostManager& postManager)
    {
        std::optional<User> loggedInUser = authManager.getLoggedInUser();

        if (!loggedInUser.has_value())
        {
            std::cout << "\nNo user is logged in.\n";
            return;
        }

        std::vector<Post> posts = postManager.getPostsByUsername(loggedInUser->getUserName());
        displayPosts(posts);
    }

    void handleLikePost(PostManager& postManager, AuthManager& authManager)
    {
        std::optional<User> loggedInUser = authManager.getLoggedInUser();

        if (!loggedInUser.has_value())
        {
            std::cout << "\nNo user is logged in.\n";
            return;
        }

        std::string authorUsername;
        std::string postId;

        readCompleteLineInput(std::cin, authorUsername, "Enter post owner username: ");
        readCompleteLineInput(std::cin, postId, "Enter post id: ");

        bool isLiked = postManager.likePost(postId,
                                            authorUsername,
                                            loggedInUser->getUserName(),
                                            loggedInUser->getName());

        if (isLiked)
        {
            std::cout << "\nPost liked successfully.\n";
        }
        else
        {
            std::cout << "\nUnable to like post.\n";
        }
    }

    void handleUnlikePost(PostManager& postManager, AuthManager& authManager)
    {
        std::optional<User> loggedInUser = authManager.getLoggedInUser();

        if (!loggedInUser.has_value())
        {
            std::cout << "\nNo user is logged in.\n";
            return;
        }

        std::string authorUsername;
        std::string postId;

        readCompleteLineInput(std::cin, authorUsername, "Enter post owner username: ");
        readCompleteLineInput(std::cin, postId, "Enter post id: ");

        bool isUnliked = postManager.unlikePost(postId,
                                                authorUsername,
                                                loggedInUser->getUserName());

        if (isUnliked)
        {
            std::cout << "\nPost unliked successfully.\n";
        }
        else
        {
            std::cout << "\nUnable to unlike post.\n";
        }
    }

    void handleAddComment(PostManager& postManager, AuthManager& authManager)
    {
        std::optional<User> loggedInUser = authManager.getLoggedInUser();

        if (!loggedInUser.has_value())
        {
            std::cout << "\nNo user is logged in.\n";
            return;
        }

        std::string authorUsername;
        std::string postId;
        std::string commentText;

        readCompleteLineInput(std::cin, authorUsername, "Enter post owner username: ");
        readCompleteLineInput(std::cin, postId, "Enter post id: ");
        readCompleteLineInput(std::cin, commentText, "Enter comment text: ");

        Comment comment(generateCommentId(),
                        loggedInUser->getUserName(),
                        loggedInUser->getName(),
                        commentText);

        bool isCommentAdded = postManager.addCommentToPost(postId,
                                                           authorUsername,
                                                           comment);

        if (isCommentAdded)
        {
            std::cout << "\nComment added successfully.\n";
        }
        else
        {
            std::cout << "\nUnable to add comment.\n";
        }
    }

    void handleLoggedInMenu(AuthManager& authManager, PostManager& postManager)
    {
        bool shouldStayLoggedIn = true;

        while (shouldStayLoggedIn && authManager.isUserLoggedIn())
        {
            printUserMenu();
            int choice = readValidUserInput(ENTER_CHOICE_PROMPT);

            switch (choice)
            {
                case 1:
                    handleCreatePost(authManager, postManager);
                    break;

                case 2:
                    handleViewAllPosts(postManager);
                    break;

                case 3:
                    handleViewMyPosts(authManager, postManager);
                    break;

                case 4:
                    handleLikePost(postManager, authManager);
                    break;

                case 5:
                    handleUnlikePost(postManager, authManager);
                    break;

                case 6:
                    handleAddComment(postManager, authManager);
                    break;

                case 7:
                    authManager.signOut();
                    std::cout << LOGGING_OUT_MESSAGE;
                    shouldStayLoggedIn = false;
                    break;

                default:
                    std::cout << INVALID_INPUT_ERROR_MESSAGE;
                    break;
            }
        }
    }
}

int main()
{
    FileUserStorage fileUserStorage("resources/users");
    FilePostStorage filePostStorage("resources/posts");
    CryptoService cryptoService("mini_instagram_key");

    UserManager userManager(fileUserStorage);
    AuthManager authManager(userManager, cryptoService);
    PostManager postManager(filePostStorage);

    bool shouldRunProgram = true;

    while (shouldRunProgram)
    {
        printMainMenu();
        int choice = readValidUserInput(ENTER_CHOICE_PROMPT);

        switch (choice)
        {
            case 1:
            {
                bool isLoginSuccessful = handleLogin(authManager);

                if (isLoginSuccessful)
                {
                    handleLoggedInMenu(authManager, postManager);
                }
                break;
            }

            case 2:
                handleSignUp(authManager);
                break;

            case 3:
                shouldRunProgram = false;
                std::cout << EXIT_PROGRAM_MESSAGE;
                break;

            default:
                std::cout << INVALID_INPUT_ERROR_MESSAGE;
                break;
        }
    }

    return 0;
}
