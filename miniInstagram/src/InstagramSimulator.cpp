#include <iostream>
#include <vector>
#include <optional>
#include <map>
#include <string>
#include <chrono>

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
#include "InstagramSimulator.h"

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

long long getCurrentTimestamp()
{
    return std::chrono::duration_cast<std::chrono::milliseconds>(
               std::chrono::system_clock::now().time_since_epoch())
        .count();
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
1. View Profile
2. Edit Profile
3. Create Post
4. Edit Post
5. View All Posts
6. View My Posts
7. Logout
============================
)";
}

void displayProfile(const User& user)
{
    std::cout << "\n=========== My Profile ===========\n";
    std::cout << "Username : " << user.getUserName() << "\n";
    std::cout << "Name     : " << user.getName() << "\n";
    std::cout << "Bio      : " << user.getBio() << "\n";
    std::cout << "==================================\n";
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

void handleViewProfile(AuthManager& authManager)
{
    std::optional<User> loggedInUser = authManager.getLoggedInUser();

    if (!loggedInUser.has_value())
    {
        std::cout << "\nNo user is logged in.\n";
        return;
    }

    displayProfile(loggedInUser.value());
}

void handleEditProfile(AuthManager& authManager, UserManager& userManager)
{
    std::optional<User> loggedInUser = authManager.getLoggedInUser();

    if (!loggedInUser.has_value())
    {
        std::cout << "\nNo user is logged in.\n";
        return;
    }

    std::cout << "\nWhat do you want to edit?\n";
    std::cout << "1. Name\n";
    std::cout << "2. Bio\n";
    std::cout << "3. Name and Bio\n";
    std::cout << "0. Back\n";

    int choice = readValidUserInput(ENTER_CHOICE_PROMPT);

    if (choice == 0)
    {
        return;
    }

    std::string updatedName = loggedInUser->getName();
    std::string updatedBio = loggedInUser->getBio();

    if (choice == 1 || choice == 3)
    {
        readCompleteLineInput(std::cin, updatedName, "Enter updated name: ");

        if (updatedName.empty())
        {
            std::cout << "Error: Name cannot be empty.\n";
            return;
        }
    }

    if (choice == 2 || choice == 3)
    {
        readCompleteLineInput(std::cin, updatedBio, "Enter updated bio: ");
    }

    if (choice != 1 && choice != 2 && choice != 3)
    {
        std::cout << INVALID_INPUT_ERROR_MESSAGE;
        return;
    }

    User updatedUser(
        loggedInUser->getUserName(),
        updatedName,
        loggedInUser->getEncryptedPassword(),
        updatedBio);

    bool isUpdated = userManager.updateUser(updatedUser);

    if (isUpdated)
    {
        authManager.updateLoggedInUser(updatedUser);
        std::cout << "\nProfile updated successfully.\n";
    }
    else
    {
        std::cout << "\nUnable to update profile.\n";
    }
}

void displayMyComments(const std::vector<Comment>& comments,
                       const std::string& loggedInUsername,
                       std::vector<int>& actualIndexes)
{
    actualIndexes.clear();

    std::cout << "\n=========== My Comments ===========\n";

    int displayNumber = 1;

    for (int index = 0; index < static_cast<int>(comments.size()); index++)
    {
        if (comments[index].getCommentedByUsername() == loggedInUsername)
        {
            std::cout << displayNumber << ". " << comments[index].getText() << "\n";
            actualIndexes.push_back(index);
            displayNumber++;
        }
    }

    if (actualIndexes.empty())
    {
        std::cout << "You have not added any comment on this post.\n";
    }

    std::cout << "===================================\n";
}

void displayAllComments(const std::vector<Comment>& comments,
                        std::vector<int>& actualIndexes)
{
    actualIndexes.clear();

    std::cout << "\n=========== Comments ===========\n";

    for (int index = 0; index < static_cast<int>(comments.size()); index++)
    {
        std::cout << (index + 1) << ". "
                  << comments[index].getCommentedByName()
                  << " : " << comments[index].getText() << "\n";
        actualIndexes.push_back(index);
    }

    if (actualIndexes.empty())
    {
        std::cout << "No comments found.\n";
    }

    std::cout << "================================\n";
}

void handleEditComment(const Post& post,
                       const User& loggedInUser,
                       PostManager& postManager)
{
    std::vector<Comment> comments = post.getComments();
    std::vector<int> actualIndexes;

    displayMyComments(comments, loggedInUser.getUserName(), actualIndexes);

    if (actualIndexes.empty())
    {
        return;
    }

    std::cout << "Enter the comment number you want to edit.\n";
    std::cout << "Press 0 to back.\n";

    int choice = readValidUserInput(ENTER_CHOICE_PROMPT);

    if (choice == 0)
    {
        return;
    }

    if (choice < 1 || choice > static_cast<int>(actualIndexes.size()))
    {
        std::cout << INVALID_INPUT_ERROR_MESSAGE;
        return;
    }

    std::string updatedText;
    readCompleteLineInput(std::cin, updatedText, "Enter updated comment: ");

    bool isEdited = postManager.editCommentInPost(
        post.getPostId(),
        post.getAuthorUsername(),
        actualIndexes[choice - 1],
        updatedText);

    if (isEdited)
    {
        std::cout << "\nComment updated successfully.\n";
    }
    else
    {
        std::cout << "\nUnable to update comment.\n";
    }
}

void handleDeleteComment(const Post& post,
                         const User& loggedInUser,
                         PostManager& postManager)
{
    std::vector<Comment> comments = post.getComments();
    std::vector<int> actualIndexes;

    bool isPostOwner = (post.getAuthorUsername() == loggedInUser.getUserName());

    if (isPostOwner)
    {
        displayAllComments(comments, actualIndexes);
    }
    else
    {
        displayMyComments(comments, loggedInUser.getUserName(), actualIndexes);
    }

    if (actualIndexes.empty())
    {
        return;
    }

    std::cout << "Enter the comment number you want to delete.\n";
    std::cout << "Press 0 to back.\n";

    int choice = readValidUserInput(ENTER_CHOICE_PROMPT);

    if (choice == 0)
    {
        return;
    }

    if (choice < 1 || choice > static_cast<int>(actualIndexes.size()))
    {
        std::cout << INVALID_INPUT_ERROR_MESSAGE;
        return;
    }

    std::cout << "\nAre you sure you want to delete this comment?\n";
    std::cout << "1. Yes\n";
    std::cout << "0. No\n";

    int confirmChoice = readValidUserInput(ENTER_CHOICE_PROMPT);

    if (confirmChoice != 1)
    {
        return;
    }

    bool isDeleted = postManager.deleteCommentFromPost(
        post.getPostId(),
        post.getAuthorUsername(),
        actualIndexes[choice - 1]);

    if (isDeleted)
    {
        std::cout << "\nComment deleted successfully.\n";
    }
    else
    {
        std::cout << "\nUnable to delete comment.\n";
    }
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
        std::cout << "3. Edit My Comment\n";

        bool isOwner = (post->getAuthorUsername() == loggedInUser->getUserName());

        if (isOwner)
        {
            std::cout << "4. Delete Any Comment\n";
            std::cout << "5. Delete Post\n";
        }
        else
        {
            std::cout << "4. Delete My Comment\n";
        }

        std::cout << "6. Back\n";

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
        else if (choice == 3)
        {
            handleEditComment(post.value(), loggedInUser.value(), postManager);
        }
        else if (choice == 4)
        {
            handleDeleteComment(post.value(), loggedInUser.value(), postManager);
        }
        else if (choice == 5 && isOwner)
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
        else if (choice == 6)
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
        content,
        getCurrentTimestamp());

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

void handleEditPost(AuthManager& authManager, PostManager& postManager)
{
    std::optional<User> loggedInUser = authManager.getLoggedInUser();

    if (!loggedInUser.has_value())
    {
        std::cout << "\nNo user is logged in.\n";
        return;
    }

    std::vector<Post> myPosts = postManager.getPostsByUsername(loggedInUser->getUserName());

    if (myPosts.empty())
    {
        std::cout << "\nYou have no posts to edit.\n";
        return;
    }

    std::cout << "\n=========== My Posts ===========\n";
    for (int index = 0; index < static_cast<int>(myPosts.size()); index++)
    {
        std::cout << (index + 1) << ". " << myPosts[index].getContent() << "\n";
    }

    std::cout << "\nEnter the post number you want to edit.\n";
    std::cout << "Press 0 to back.\n";

    int choice = readValidUserInput(ENTER_CHOICE_PROMPT);

    if (choice == 0)
    {
        return;
    }

    if (choice < 1 || choice > static_cast<int>(myPosts.size()))
    {
        std::cout << INVALID_INPUT_ERROR_MESSAGE;
        return;
    }

    Post selectedPost = myPosts[choice - 1];

    std::string updatedContent;
    readCompleteLineInput(std::cin, updatedContent, "Enter updated content: ");

    bool isUpdated = postManager.updatePostContent(
        selectedPost.getPostId(),
        selectedPost.getAuthorUsername(),
        updatedContent);

    if (isUpdated)
    {
        std::cout << "\nPost updated successfully.\n";
    }
    else
    {
        std::cout << "\nUnable to update post.\n";
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

void handleLoggedInMenu(AuthManager& authManager,
                        UserManager& userManager,
                        PostManager& postManager)
{
    while (authManager.isUserLoggedIn())
    {
        printUserMenu();
        int choice = readValidUserInput(ENTER_CHOICE_PROMPT);

        switch (choice)
        {
            case 1:
                handleViewProfile(authManager);
                break;

            case 2:
                handleEditProfile(authManager, userManager);
                break;

            case 3:
                handleCreatePost(authManager, postManager);
                break;

            case 4:
                handleEditPost(authManager, postManager);
                break;

            case 5:
                handlePostList(postManager.getAllPosts(), authManager, postManager);
                break;

            case 6:
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

            case 7:
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

void runInstagramSimulator()
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
                handleLoggedInMenu(authManager, userManager, postManager);
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
}
