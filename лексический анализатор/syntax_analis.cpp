#include "syntax_analis.h"

//Функция, которая возвращает значение True или False, в зависимости от сборки дерево Program
bool syntax_analis::Program(Tree_of_syntax& Tree)
{
    //Cоздаём дерево для Begin
    Tree_of_syntax tree_of_Begin("Begin");
    //Проверяем, что дерево нормально собралось
    if (!Begin(tree_of_Begin))
    {
        return false;
    }
    //Добавляем дерево в Program
    Tree.addSon("Begin", "Program", Tree.get_our_root());
    Tree.insert_new_subtree(tree_of_Begin, "Begin", Tree.get_our_root());

    //Cоздаём дерево для Descriptions
    Tree_of_syntax tree_of_Descriptions("Descriptions");
    //Проверяем, что дерево нормально собралось
    if (!Descriptions(tree_of_Descriptions))
    {
        return false;
    }
    //Добавляем дерево в Program
    Tree.addSon("Descriptions", "Program", Tree.get_our_root());
    Tree.insert_new_subtree(tree_of_Descriptions, "Descriptions", Tree.get_our_root());

    //Cоздаём дерево для Operators
    Tree_of_syntax tree_of_Operators("Operators");
    //Проверяем, что дерево нормально собралось
    if (!Operators(tree_of_Operators))
    {
        return false;
    }
    //Добавляем дерево в Program
    Tree.addSon("Operators", "Program", Tree.get_our_root());
    Tree.insert_new_subtree(tree_of_Operators, "Operators", Tree.get_our_root());

    //Cоздаём дерево для End
    Tree_of_syntax tree_of_End("End");
    //Проверяем, что дерево нормально собралось
    if (!End(tree_of_End))
    {
        return false;
    }
    //Добавляем дерево в Program
    Tree.addSon("End", "Program", Tree.get_our_root());
    Tree.insert_new_subtree(tree_of_End, "End", Tree.get_our_root());

    //Проверка, что мы дошли до конца файла и последнее считывание у нас имеет None
    bool flag = false;
    if (lex.add_new_unique_value(in, table).name == "None")
    {
        flag = true;
    }
    return flag;
}
//Функция, которая возвращает значение True или False, в зависимости от сборки дерево Begin
bool syntax_analis::Begin(Tree_of_syntax& Tree)
{
    //Считываем слово из потока, даем ему грубо говоря "токен"
    unique_value value = lex.add_new_unique_value(in, table);

    //Проверяем, что слово соответствует лексеме
    if (value.name != "PROGRAM")
    {
        cout << "Ошибка!\nНашлось " << value.name << " Ожидалось Program";
        return 0;
    }
    //Поняли, что слово правильное, добавляем в Begin
    Tree.addSon(value.type + " :  " + value.name , "Begin", Tree.get_our_root());

    //Считываем следующие слово из потока, даем ему грубо говоря "токен"
    value = lex.add_new_unique_value(in, table);

    //Проверяем, что слово соответствует лексеме
    if (value.type != "Id")
    {
        cout << "Ошибка!\nНашлось " << value.name << " Ожидалось Id";
        return 0;
    }
    //Поняли, что слово правильное, добавляем в Begin
    Tree.addSon(value.type + " :  " + value.name , "Begin", Tree.get_our_root());

    //Дерево успешно собралось, возвращаем True
    return 1;
}
bool flag_for_Descr = false;
//Функция, которая возвращает значение True или False, в зависимости от сборки дерево Descriptions
bool syntax_analis::Descriptions(Tree_of_syntax& Tree)
{
    //Считываем слово из потока, даем ему грубо говоря "токен"
    unique_value value = lex.add_new_unique_value(in, table);


    if (value.name != "INTEGER" && value.name !="REAL")
    {
        if (!flag_for_Descr)
            return 0;
        lex.back_word(in, value.name);
        Tree.get_our_root().get_data() = "";
        return 1;
    }

    lex.back_word(in, value.name);

    //объявляем новое поддерево 
    Tree_of_syntax subtree_of_descr("Descr");


    if (!Descr(subtree_of_descr))
    {
        return 0;
    }
    flag_for_Descr = true;
    //вставляем его 
    Tree.insert_child(subtree_of_descr, "Descriptions", Tree.get_our_root());
    Tree_of_syntax buffer("Descriptions");
    Tree.addSon("Descriptions", Tree.get_our_root().get_data(), Tree.get_our_root());
    if (!Descriptions(buffer))
    {
        return 0;
    }
    Tree.insert_new_subtree(buffer, Tree.get_our_root().get_data(), Tree.get_our_root());

    //Дерево успешно собралось, возвращаем True
    return 1;

}
//Функция, которая возвращает значение True или False, в зависимости от сборки дерево Descr
bool syntax_analis::Descr(Tree_of_syntax& Tree)
{
    Tree_of_syntax buffer("Type");
    if (!Type(buffer))
    {
        return 0;
    }
    Tree.addSon("Type", "Descr", Tree.get_our_root());
    Tree.insert_new_subtree(buffer, "Type", Tree.get_our_root());
    Tree_of_syntax temp("Varlist");
    if (!Varlist(temp))
    {
        return 0;
    }
    Tree.addSon("Varlist", "Descr", Tree.get_our_root());
    Tree.insert_new_subtree(temp, "Varlist", Tree.get_our_root());

    //Дерево успешно собралось, возвращаем True
    return 1;
}
//Функция, которая возвращает значение True или False, в зависимости от сборки дерево Type
bool syntax_analis::Type(Tree_of_syntax& Tree)
{
    //Считываем следующие слово из потока, даем ему грубо говоря "токен"
    unique_value value = lex.add_new_unique_value(in, table);

    //Проверяем, что слово соответствует лексеме
    if (value.name != "INTEGER" && value.name !="REAL")
    {
        cout << "Ошибка!\nНашлось " << value.name << " Ожидалось INTEGER или REAL";
        return 0;
    }
    Tree.addSon(value.type + " :  " + value.name , Tree.get_our_root().get_data(), Tree.get_our_root());
}
//Функция, которая возвращает значение True или False, в зависимости от сборки дерево Varlist
bool syntax_analis::Varlist(Tree_of_syntax& Tree)
{
    //Считываем следующие слово из потока, даем ему грубо говоря "токен"
    unique_value value = lex.add_new_unique_value(in, table);

    //Проверяем, что слово соответствует лексеме
    if (value.type != "Id")
    {
        cout << "Ошибка!\nНашлось  " << value.name << "   Ожидалось ID";
        return 0;
    }

    //Добавляем сына к Varlist
    Tree.addSon(value.type + " :  " + value.name , "Varlist", Tree.get_our_root());

    //Считываем следующие слово из потока, даем ему грубо говоря "токен"
    value = lex.add_new_unique_value(in, table);

    if (value.name != ",")
    {
        lex.back_word(in, value.name);
        return 1;
    }

    Tree.addSon(value.type + " :  " + value.name , "Varlist", Tree.get_our_root());
    Tree_of_syntax buffer("Varlist");
    if (!Varlist(buffer))
    {
        return 0;
    }
    Tree.addSon("Varlist", "Varlist", Tree.get_our_root());
    Tree.insert_new_subtree(buffer, "Varlist", Tree.get_our_root());

    //Дерево успешно собралось, возвращаем True
    return 1;
}
bool flag = false;
//Функция, которая возвращает значение True или False, в зависимости от сборки дерево Operators
bool syntax_analis::Operators(Tree_of_syntax& Tree)
{
    //Считываем следующие слово из потока, даем ему грубо говоря "токен"
    unique_value value = lex.add_new_unique_value(in, table);

    if (value.type != "Id" && value.name != "CALL")
    {
        if (!flag)
        {
            return 0;
        }
        lex.back_word(in, value.name);
        Tree.get_our_root().get_data() = "";
        return 1;
    }

    lex.back_word(in, value.name);

    Tree_of_syntax buffer("Op");
    if (!Op(buffer))
    {
        return 0;
    }
    flag = true;
    Tree.insert_child(buffer, "Operators", Tree.get_our_root());
    Tree_of_syntax tmp("Operators");
    Tree.addSon("Operators", Tree.get_our_root().get_data(), Tree.get_our_root());
    if (!Operators(tmp))
    {
        return 0;
    }
    Tree.insert_new_subtree(tmp, Tree.get_our_root().get_data(), Tree.get_our_root());

    //Дерево успешно собралось, возвращаем True
    return 1;
}
//Функция, которая возвращает значение True или False, в зависимости от сборки дерево Op
bool syntax_analis::Op(Tree_of_syntax& Tree)
{
    Tree_of_syntax temp;

    //Считываем следующие слово из потока, даем ему грубо говоря "токен"
    unique_value value = lex.add_new_unique_value(in, table);

    //Проверяем, что слово соответствует лексеме
    if (value.type == "Id")
    {
        Tree.addSon(value.type + " :  " + value.name , "Op", Tree.get_our_root());
        //Считываем следующие слово из потока, даем ему грубо говоря "токен"
        value = lex.add_new_unique_value(in, table);

        //Проверяем, что слово соответствует лексеме
        if (value.name != "=")
        {
            cout << "Ошибка!\nНашлось " << value.name << " Ожидалось знак \"=\" ";
            return 0;
        }
        Tree.addSon(value.type + " :  " + value.name , "Op", Tree.get_our_root());
        temp.clear_childs();
        Tree_of_syntax tempp("Expr");
        if (!Expr(tempp))
        {
            return 0;
        }
        Tree.addSon("Expr", "Op", Tree.get_our_root());
        Tree.insert_new_subtree(tempp, "Expr", Tree.get_our_root());
        tempp.clear_childs();
    }
    //Проверяем, что слово соответствует лексеме
    else if (value.name == "CALL")
    {
        Tree.addSon(value.type + " :  " + value.name , "Op", Tree.get_our_root());

        //Считываем следующие слово из потока, даем ему грубо говоря "токен"
        value = lex.add_new_unique_value(in, table);
        if (value.type != "Id")
        {
            cout << "Ошибка!\nНашлось " << value.name << " Ожидалось Id ";
            return 0;
        }
        Tree.addSon(value.type + " :  " + value.name , "Op", Tree.get_our_root());

        //Считываем следующие слово из потока, даем ему грубо говоря "токен"
        value = lex.add_new_unique_value(in, table);
        //Проверяем, что слово соответствует лексеме
        if (value.name != "(")
        {
            cout << "Ошибка!\nНашлось " << value.name << " Ожидалось знак ( ";
            return 0;
        }
        Tree.addSon(value.type + " :  " + value.name , "Op", Tree.get_our_root());

        temp.clear_childs();
        Tree_of_syntax tempp("Varlist");
        if (!Varlist(tempp))
        {
            return 0;
        }
        Tree.addSon("Varlist", "Op", Tree.get_our_root());
        Tree.insert_new_subtree(tempp, "Varlist", Tree.get_our_root());

        //Считываем следующие слово из потока, даем ему грубо говоря "токен"
        value = lex.add_new_unique_value(in, table);

        //Проверяем, что слово соответствует лексеме
        if (value.name != ")")
        {
            cout << "Ошибка!\nНашлось " << value.name << " Ожидалось ) ";
            return 0;
        }
        Tree.addSon(value.type + " :  " + value.name , "Op", Tree.get_our_root());

        
    }
    else
    {
        cout << "Ошибка!\nНашлось " << value.name << " Ожидалось переменная или CALL \n";
        return 0;
    }
    //Дерево успешно собралось, возвращаем True
    return 1;
}
//Функция, которая возвращает значение True или False, в зависимости от сборки дерево SimpleExpr
bool syntax_analis::SimpleExpr(Tree_of_syntax& Tree)
{
    //Считываем слово из потока, даем ему грубо говоря "токен"
    unique_value value = lex.add_new_unique_value(in, table);

    //Проверяем, что слово соответствует лексеме
    if (value.name == "(")
    {
        Tree.addSon(value.type + " :  " + value.name , "SimpleExpr", Tree.get_our_root());
        Tree_of_syntax buffer("Expr");
        if (!Expr(buffer))
        {
            return 0;
        }
        Tree.addSon("Expr", "SimpleExpr", Tree.get_our_root());
        Tree.insert_new_subtree(buffer, "Expr", Tree.get_our_root());
        value = lex.add_new_unique_value(in, table);
        //Проверяем, что слово соответствует лексеме
        if (value.name != ")")
        {
            cout << "Ошибка!\nНашлось " << value.name << " Ожидалось )\" ";
            return 0;
        }
    }
    //Проверяем, что слово соответствует лексеме
    else if (value.type != "Id" && value.type != "int_num" && value.type != "real_num")
    {
        cout << "Ошибка!\nНашлось " << value.name << " Ожидались либо число либо переменная ";
        return 0;
    }

    //Поняли, что слово правильное, добавляем в SimpleExpr
    Tree.addSon(value.type + " :  " + value.name , "SimpleExpr", Tree.get_our_root());

    //Дерево успешно собралось, возвращаем True
    return 1;
}
//Функция, которая возвращает значение True или False, в зависимости от сборки дерево Expr
bool syntax_analis::Expr(Tree_of_syntax& Tree)
{
    //Cоздём дерево для SimpleExpr
    Tree_of_syntax buffer("SimpleExpr");

    //Проверяем, что дерево успешно собралось
    if (!SimpleExpr(buffer))
    {
        return 0;
    }

    //Добавляем успешно собранное дерево в Expr 
    Tree.addSon("SimpleExpr", "Expr", Tree.get_our_root());
    Tree.insert_new_subtree(buffer, "SimpleExpr", Tree.get_our_root());

    //Считываем следующие слово из потока, даем ему грубо говоря "токен"
    unique_value value = lex.add_new_unique_value(in, table);


    if (value.name != "-" && value.name != "+")
    {
        lex.back_word(in, value.name);
        return 1;
    }

    //Поняли, что слово правильное, добавляем в End
    Tree.addSon(value.type + " :  " + value.name , "Expr", Tree.get_our_root());

    //Рекурсивно запускаемся заново 
    if (!Expr(Tree))
    {
        return 0;
    }

    //Дерево успешно собралось, возвращаем True
    return 1;
}

//Функция, которая возвращает значение True или False, в зависимости от сборки дерево End
bool syntax_analis::End(Tree_of_syntax& Tree)
{
    //Считываем слово из потока, даем ему грубо говоря "токен"
    unique_value value = lex.add_new_unique_value(in, table);

    //Проверяем, что слово соответствует лексеме
    if (value.name != "END")
    {
        cout << "Ошибка!\nНашлось " << value.name << " Ожидался END";
        return 0;
    }
    //Поняли, что слово правильное, добавляем в End
    Tree.addSon(value.type + " :  " + value.name , "End", Tree.get_our_root());

    //Считываем следующие слово из потока, даем ему грубо говоря "токен"
    value = lex.add_new_unique_value(in, table);;

    //Проверяем, что слово соответствует лексеме
    if (value.type != "Id")
    {
        cout << "Ошибка!\nНашлось " << value.name << " Ожидалась переменная";
        return 0;
    }
    //Поняли, что слово правильное, добавляем в End
    Tree.addSon(value.type + " :  " + value.name , "End", Tree.get_our_root());

    //Дерево успешно собралось, возвращаем True
    return 1;
}
