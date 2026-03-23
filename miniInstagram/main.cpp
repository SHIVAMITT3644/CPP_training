#include <iostream>
#include <vector>
#include <optional>
#include <map>
#include <string>

#include "Constants.h"
#include "Input.h"
#include "User.h"
#include "Comment.h"
#include "Post.h"
#include "CryptoService.h"
#include "FileUserStorage.h"
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

    std::string generatePostId()
    {
        return "post" + std::to_string(generatePostNumber());
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
4. Logout
============================
)";
    }

    void displaySinglePost(const Post& post)
    {
        std::cout << "\n----------------------------------\n";
        std::cout << "Post ID   : " << post.getPostId() << "\n";
        std::cout << "Author    : " << post.getAuthorName() << "\n";
        std::cout << "Content   : " << post.getContent() << "\n";
        std::cout << "Likes     : " << post.getLikeCount() << "\n";

        std::cout << "Liked By  : ";
        std::map<std::string, std::string> likedUsers = post.getLikedUsers();

        if (likedUsers.empty())
        {
            std::cout << "No likes yet";
        }
        else
        {
            for (const auto& likedUser : likedUsers)
            {
                std::cout << likedUser.second << "  ";
            }
        }

        std::cout << "\n\nComments:\n";

        std::vector<Comment> comments = post.getComments();

        if (comments.empty())
        {
            std::cout << "No comments yet\n";
        }
        else
        {
            for (const Comment& comment : comments)
            {
                std::cout << comment.getCommentedByName()
                          << " : " << comment.getText() << "\n";
            }
        }

        std::cout << "----------------------------------\n";
    }

    void handleSelectedPost(Post selectedPost,
                            AuthManager& authManager,
                            PostManager& postManager)
    {
        std::optional<User> loggedInUser = authManager.getLoggedInUser();

        if (!loggedInUser.has_value())
        {
            return;
        }

        while (true)
        {
            std::optional<Post> post = postManager.getPostById(
                selectedPost.getPostId(),
                selectedPost.getAuthorUsername());

            if (!post.has_value())
            {
                std::cout << "\nPost no longer exists.\n";
                return;
            }

            displaySinglePost(post.value());

            if (post->hasLiked(loggedInUser->getUserName()))
            {
                std::cout << "1. Unlike Post\n";
            }
            else
            {
                std::cout << "1. Like Post\n";
            }

            std::cout << "2. Add Comment\n";

            bool isOwner = (post->getAuthorUsername() == loggedInUser->getUserName());

            if (isOwner)
            {
                std::cout << "3. Delete Post\n";
            }

            std::cout << "0. Back\n";

            int choice = readValidUserInput(ENTER_CHOICE_PROMPT);

            if (choice == 1)
            {
                if (post->hasLiked(loggedInUser->getUserName()))
                {
                    bool isUnliked = postManager.unlikePost(
                        post->getPostId(),
                        post->getAuthorUsername(),
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
                else
                {
                    bool isLiked = postManager.likePost(
                        post->getPostId(),
                        post->getAuthorUsername(),
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
            }
            else if (choice == 2)
            {
                std::string commentText;
                readCompleteLineInput(std::cin, commentText, "Enter comment: ");

                Comment comment(
                    loggedInUser->getUserName(),
                    loggedInUser->getName(),
                    commentText);

                bool isCommentAdded = postManager.addCommentToPost(
                    post->getPostId(),
                    post->getAuthorUsername(),
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
            else if (choice == 3 && isOwner)
            {
                std::cout << "\nAre you sure you want to delete this post?\n";
                std::cout << "1. Yes\n";
                std::cout << "0. No\n";

                int confirmChoice = readValidUserInput(ENTER_CHOICE_PROMPT);

                if (confirmChoice == 1)
                {
                    bool isDeleted = postManager.deletePost(
                        post->getPostId(),
                        post->getAuthorUsername());

                    if (isDeleted)
                    {
                        std::cout << "\nPost deleted successfully.\n";
                    }
                    else
                    {
                        std::cout << TECHNICAL_ERROR_MESSAGE;
                    }

                    return;
                }
            }
            else if (choice == 0)
            {
                return;
            }
            else
            {
                std::cout << INVALID_INPUT_ERROR_MESSAGE;
            }
        }
    }

    void handlePostList(const std::vector<Post>& posts,
                        AuthManager& authManager,
                        PostManager& postManager)
    {
        if (posts.empty())
        {
            std::cout << "\nNo posts found.\n";
            return;
        }

        while (true)
        {
            std::cout << "\n=========== Posts ===========\n";

            for (int index = 0; index < static_cast<int>(posts.size()); index++)
            {
                std::cout << (index + 1) << ". "
                          << posts[index].getAuthorName()
                          << " : " << posts[index].getContent() << "\n";
            }

            std::cout << "\nEnter the choice you want to open a post.\n";
            std::cout << "Press 0 to back.\n";

            int choice = readValidUserInput(ENTER_CHOICE_PROMPT);

            if (choice == 0)
            {
                return;
            }
            else if (choice >= 1 && choice <= static_cast<int>(posts.size()))
            {
                handleSelectedPost(posts[choice - 1], authManager, postManager);
            }
            else
            {
                std::cout << INVALID_INPUT_ERROR_MESSAGE;
            }
        }
    }

    void handleSignUp(AuthManager& authManager, UserManager& userManager)
    {
        std::string username;
        std::string fullName;
        std::string password;
        std::string bio;

        readCompleteLineInput(std::cin, username, USERNAME_INPUT_PROMPT);
        readCompleteLineInput(std::cin, fullName, "Enter full name: ");
        password = readHiddenPassword(PASSWORD_INPUT_PROMPT);
        readCompleteLineInput(std::cin, bio, "Enter bio: ");

        if (username.length() < 5)
        {
            std::cout << "Error: Username must be at least 5 characters long.\n";
            return;
        }

        if (fullName.empty())
        {
            std::cout << "Error: Name cannot be empty.\n";
            return;
        }

        if (password.length() < 5)
        {
            std::cout << "Error: Password must be at least 5 characters long.\n";
            return;
        }

        if (userManager.userExists(username))
        {
            std::cout << "Error: Username already exists. Please choose another username.\n";
            return;
        }

        bool isSignUpSuccessful = authManager.signUp(username, fullName, password, bio);

        if (isSignUpSuccessful)
        {
            std::cout << ACCOUNT_CREATED_MESSAGE << username << "\n";
        }
        else
        {
            std::cout << "Error: Unable to create account.\n";
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

        Post post(
            generatePostId(),
            loggedInUser->getUserName(),
            loggedInUser->getName(),
            content);

        bool isPostCreated = postManager.createPost(post);

        if (isPostCreated)
        {
            std::cout << "\nPost created successfully.\n";
        }
        else
        {
            std::cout << TECHNICAL_ERROR_MESSAGE;
        }
    }

    void handleLoggedInMenu(AuthManager& authManager, PostManager& postManager)
    {
        while (authManager.isUserLoggedIn())
        {
            printUserMenu();
            int choice = readValidUserInput(ENTER_CHOICE_PROMPT);

            switch (choice)
            {
                case 1:
                    handleCreatePost(authManager, postManager);
                    break;

                case 2:
                    handlePostList(postManager.getAllPosts(), authManager, postManager);
                    break;

                case 3:
                {
                    std::optional<User> loggedInUser = authManager.getLoggedInUser();

                    if (loggedInUser.has_value())
                    {
                        handlePostList(
                            postManager.getPostsByUsername(loggedInUser->getUserName()),
                            authManager,
                            postManager);
                    }
                    break;
                }

                case 4:
                    authManager.signOut();
                    std::cout << LOGGING_OUT_MESSAGE;
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

    while (true)
    {
        printMainMenu();
        int choice = readValidUserInput(ENTER_CHOICE_PROMPT);

        if (choice == 1)
        {
            bool isLoginSuccessful = handleLogin(authManager);

            if (isLoginSuccessful)
            {
                handleLoggedInMenu(authManager, postManager);
            }
        }
        else if (choice == 2)
        {
            handleSignUp(authManager, userManager);
        }
        else if (choice == 3)
        {
            std::cout << EXIT_PROGRAM_MESSAGE;
            break;
        }
        else
        {
            std::cout << INVALID_INPUT_ERROR_MESSAGE;
        }
    }

    return 0;
}
