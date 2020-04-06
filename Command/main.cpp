//
//  main.cpp
//  Command
//
//  Created by Arina Nazarova on 04.04.2020.
//  Copyright © 2020 Arina Nazarova. All rights reserved.
//



#include<iostream>
#include<vector>
#include<string>
using namespace std;

class Game
{
public:
    void create( ) {
        cout << "Игра создана " << endl;
    }
    void open( string file ) {
        cout << "Откурыть игру из " << file << endl;
    }
    void save( string file ) {
        cout << "Сохранить игру в " << file << endl;
    }
    void make_move( string move ) {
        cout << "Игрок поставил " << move << endl;
    }
};

string getPlayerInput( string prompt ) {
    string input;
    cout << prompt;
    cin >> input;
    return input;
}

// Базовый класс
class Command
{
public:
    virtual ~Command() {}
    virtual void execute() = 0;
protected:
    Command( Game* p ): pgame( p) {}
    Game * pgame;
};

class CreateGameCommand: public Command
{
public:
    CreateGameCommand( Game * p ) : Command( p) {}
    void execute() {
        pgame->create( );
    }
};

class OpenGameCommand: public Command
{
public:
    OpenGameCommand( Game * p ) : Command( p) {}
    void execute() {
        string file_name;
        file_name = getPlayerInput( "Введите имя файла:");
        pgame->open( file_name);
    }
};

class SaveGameCommand: public Command
{
public:
    SaveGameCommand( Game * p ) : Command( p) {}
    void execute( ) {
        string file_name;
        file_name = getPlayerInput( "Введите имя файла :");
        pgame->save( file_name);
    }
};

class MakeMoveCommand: public Command
{
public:
    MakeMoveCommand( Game * p) : Command( p) {}
    void execute() {
        // Сохраним игру для возможного последующего отката
        pgame->save( "File");
        string move;
        move = getPlayerInput( "Введите ваш ход: крестик 'X' или нолик '0':");
        pgame->make_move( move);
    }
};

class UndoCommand: public Command
{
public:
    UndoCommand( Game * p ) : Command( p) {}
    void execute() {
        // Восстановим игру из временного файла
        pgame->open( "File");
    }
};


int main()
{
    Game game;
    // Имитация действий игрока
    vector<Command*> v;
    // Создаем новую игру
    v.push_back( new CreateGameCommand( &game));
    // Делаем несколько ходов
    v.push_back( new MakeMoveCommand( &game));
    v.push_back( new MakeMoveCommand( &game));
    // Последний ход отменяем
    v.push_back( new UndoCommand( &game));
    // Сохраняем игру
    v.push_back( new SaveGameCommand( &game));
    
    for (size_t i=0; i<v.size(); ++i)
        v[i]->execute();
    
    for (size_t i=0; i<v.size(); ++i)
        delete v[i];
    
    return 0;
}
