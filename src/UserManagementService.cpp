#include "../include/UserManagementService.h"
#include <iostream>

extern json usersData;
extern bool saveJSON(const string& filename, const json& data);

vector<UserInfo> UserManagementService::getAllUsers() {
    vector<UserInfo> result;
    
    for (const auto& user : usersData) {
        UserInfo info;
        info.id = user["id"];
        info.username = user["username"];
        info.role = user["role"];
        info.email = user.contains("email") ? user["email"].get<string>() : "N/A";
        info.loyaltyPoints = user.contains("loyaltyPoints") ? user["loyaltyPoints"].get<int>() : 0;
        result.push_back(info);
    }
    
    return result;
}

bool UserManagementService::addUser(const string& username, const string& password, const string& role, const string& email) {

    for (const auto& user : usersData) {
        if (user["username"] == username) {
            cout << "\nError: Username already exists!" << endl;
            return false;
        }
    }
    
    if (role != "Passenger" && role != "Administrator" && role != "BookingAgent") {
        cout << "\nError: Invalid role!" << endl;
        return false;
    }
    
    int newId = getNextUserId();
    
    json newUser = {
        {"id", newId},
        {"username", username},
        {"password", password},
        {"role", role},
        {"email", email}
    };
    
    if (role == "Passenger") {
        newUser["loyaltyPoints"] = 0;
        newUser["frequentFlyerNumber"] = "FF" + to_string(newId);
    }
    
    usersData.push_back(newUser);
    
    bool saved = saveJSON("data/users.json", usersData);
    
    if (saved) {
        cout << "\n User added successfully!" << endl;
        cout << "User ID: " << newId << endl;
        cout << "Username: " << username << endl;
        cout << "Role: " << role << endl;
    }
    
    return saved;
}

bool UserManagementService::deleteUser(int userId) {
    
    auto it = usersData.begin();
    bool found = false;
    
    for (; it != usersData.end(); ++it) {
        if ((*it)["id"] == userId) {
            found = true;
            break;
        }
    }
    
    if (!found) {
        cout << "\nError: User not found!" << endl;
        return false;
    }
    
    if ((*it)["role"] == "Administrator") {
        cout << "\nError: Cannot delete Administrator accounts!" << endl;
        return false;
    }
    
    usersData.erase(it);
    
    bool saved = saveJSON("data/users.json", usersData);
    
    if (saved) {
        cout << "\n User deleted successfully!" << endl;
    }
    
    return saved;
}

bool UserManagementService::updateUser(int userId, const string& email, const string& role) {
    json* user = nullptr;
    for (auto& u : usersData) {
        if (u["id"] == userId) {
            user = &u;
            break;
        }
    }
    
    if (user == nullptr) {
        cout << "\nError: User not found!" << endl;
        return false;
    }

    if (!email.empty()) {
        (*user)["email"] = email;
    }
    if (!role.empty() && role != (*user)["role"]) {
        (*user)["role"] = role;
    }
    
    bool saved = saveJSON("data/users.json", usersData);
    
    if (saved) {
        cout << "\n User updated successfully!" << endl;
    }
    
    return saved;
}

int UserManagementService::getNextUserId() {
    int maxId = 0;
    for (const auto& user : usersData) {
        int id = user["id"];
        if (id > maxId) {
            maxId = id;
        }
    }
    return maxId + 1;
}
