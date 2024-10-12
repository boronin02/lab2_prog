#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

// Определение структур

typedef struct {
    int id;
    char name[50];
    char login[50];
    char password[50];
    char created_date[50];
    float balance;
} User;

typedef struct {
    int id;
    char name[50];
    int max_bet;
    int min_bet;
    float payout_ratio; // Процент выплат
} Slot;

typedef struct {
    int id;
    int user_id;
    float amount;
    char timestamp[20]; // Время транзакции
} Transaction;

typedef struct {
    Transaction transactions[100];
    int count;
} TransactionList;

typedef struct {
    Slot slot;
    User user;
    int id;
    int user_id;
    int slot_id;
    float bet_amount;   // Сумма ставки
    float win_amount;   // Сумма выигрыша
    char play_date[20]; // Дата игры
} GameHistory;

typedef struct {
    GameHistory games[100];
    int count;
} GameHistoryList;

typedef struct {
    int id;
    int user_id;
    float bonus_amount;
    char reason[100];   // Причина бонуса
} Bonus;

typedef struct {
    Bonus bonuses[100];
    int count;
} BonusList;

typedef struct {
    User users[100];
    int count;
} Leaderboard;

// Функции

void init_user(User* user, int id, const char* name, const char* login, const char* password, const char* created_date, float balance) {
    user->id = id;
    strncpy(user->name, name, sizeof(user->name));
    strncpy(user->login, login, sizeof(user->login));
    strncpy(user->password, password, sizeof(user->password));
    strncpy(user->created_date, created_date, sizeof(user->created_date));
    user->balance = balance;
}

void init_slot(Slot* slot, int id, const char* name, int max_bet, int min_bet, float payout_ratio) {
    slot->id = id;
    strncpy(slot->name, name, sizeof(slot->name));
    slot->max_bet = max_bet;
    slot->min_bet = min_bet;
    slot->payout_ratio = payout_ratio;
}

void add_transaction(TransactionList* transaction_list, Transaction transaction) {
    if (transaction_list->count < 100) {
        transaction_list->transactions[transaction_list->count] = transaction;
        transaction_list->count++;
    }
}

void add_game(GameHistoryList* game_history_list, GameHistory game_history) {
    if (game_history_list->count < 100) {
        game_history_list->games[game_history_list->count] = game_history;
        game_history_list->count++;
    }
}

void add_bonus(BonusList* bonus_list, Bonus bonus) {
    if (bonus_list->count < 100) {
        bonus_list->bonuses[bonus_list->count] = bonus;
        bonus_list->count++;
    }
}

void add_to_leaderboard(Leaderboard* leaderboard, User user) {
    if (leaderboard->count < 100) {
        leaderboard->users[leaderboard->count] = user;
        leaderboard->count++;
    }
}

void sort_leaderboard_by_balance(Leaderboard* leaderboard) {
    for (int i = 0; i < leaderboard->count - 1; i++) {
        for (int j = 0; j < leaderboard->count - i - 1; j++) {
            if (leaderboard->users[j].balance < leaderboard->users[j + 1].balance) {
                User temp = leaderboard->users[j];
                leaderboard->users[j] = leaderboard->users[j + 1];
                leaderboard->users[j + 1] = temp;
            }
        }
    }
}

int main() {
    setlocale(LC_ALL, "Russian");

    User user1, user2, user3;
    Slot slot;
    TransactionList transaction_list;
    GameHistoryList game_history_list;
    BonusList bonus_list;
    Leaderboard leaderboard;

    transaction_list.count = 0;
    game_history_list.count = 0;
    bonus_list.count = 0;
    leaderboard.count = 0;

    // Инициализация юзеров
    init_user(&user1, 1, "Леха", "леха123", "password123", "2024-10-08", 1000.0);
    init_user(&user2, 2, "Андрюха", "андрюха52", "password456", "2024-10-08", 1500.0);
    init_user(&user3, 3, "Салфетка", "салфетка52", "password789", "2024-10-08", 2000.0);

    // Инициализация слота
    init_slot(&slot, 1, "Lucky 7", 100, 10, 0.95);

    // Пример транзакции
    Transaction transaction = { 1, user1.id, 50.0, "2024-10-08 10:00:00" };
    add_transaction(&transaction_list, transaction);

    // Пример игры
    GameHistory game_history = { slot, user1, 1, user1.id, slot.id, 50.0, 100.0, "2024-10-08 10:05:00" };
    add_game(&game_history_list, game_history);

    // Пример бонуса
    Bonus bonus = { 1, user1.id, 10.0, "Бонус Lucky 7" };
    add_bonus(&bonus_list, bonus);

    // Добавление пользователей в таблицу лидеров
    add_to_leaderboard(&leaderboard, user1);
    add_to_leaderboard(&leaderboard, user2);
    add_to_leaderboard(&leaderboard, user3);

    // Сортировка таблицы лидеров по балансу
    sort_leaderboard_by_balance(&leaderboard);

    // Вывод информации
    printf("Пользователь: %s, Баланс: %.2f\n", user1.name, user1.balance);
    printf("Слот: %s, Макс ставка: %d, Мин ставка: %d, Выплата: %.2f\n", slot.name, slot.max_bet, slot.min_bet, slot.payout_ratio);
    printf("Транзакция: %.2f в %s\n", transaction.amount, transaction.timestamp);
    printf("Сумма ставки: %.2f, Сумма выигрыша: %.2f в %s\n", game_history.bet_amount, game_history.win_amount, game_history.play_date);
    printf("Сумма бонуса: %.2f %s\n", bonus.bonus_amount, bonus.reason);

    printf("\nТаблица лидеров:\n");
    for (int i = 0; i < leaderboard.count; i++) {
        printf("Пользователь %d: %s, Баланс: %.2f\n", leaderboard.users[i].id, leaderboard.users[i].name, leaderboard.users[i].balance);
    }

    return 0;
}