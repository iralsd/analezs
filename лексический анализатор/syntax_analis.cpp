#include "syntax_analis.h"

//�������, ������� ���������� �������� True ��� False, � ����������� �� ������ ������ Program
bool syntax_analis::Program(Tree_of_syntax& Tree)
{
    //C����� ������ ��� Begin
    Tree_of_syntax tree_of_Begin("Begin");
    //���������, ��� ������ ��������� ���������
    if (!Begin(tree_of_Begin))
    {
        return false;
    }
    //��������� ������ � Program
    Tree.addSon("Begin", "Program", Tree.get_our_root());
    Tree.insert_new_subtree(tree_of_Begin, "Begin", Tree.get_our_root());

    //C����� ������ ��� Descriptions
    Tree_of_syntax tree_of_Descriptions("Descriptions");
    //���������, ��� ������ ��������� ���������
    if (!Descriptions(tree_of_Descriptions))
    {
        return false;
    }
    //��������� ������ � Program
    Tree.addSon("Descriptions", "Program", Tree.get_our_root());
    Tree.insert_new_subtree(tree_of_Descriptions, "Descriptions", Tree.get_our_root());

    //C����� ������ ��� Operators
    Tree_of_syntax tree_of_Operators("Operators");
    //���������, ��� ������ ��������� ���������
    if (!Operators(tree_of_Operators))
    {
        return false;
    }
    //��������� ������ � Program
    Tree.addSon("Operators", "Program", Tree.get_our_root());
    Tree.insert_new_subtree(tree_of_Operators, "Operators", Tree.get_our_root());

    //C����� ������ ��� End
    Tree_of_syntax tree_of_End("End");
    //���������, ��� ������ ��������� ���������
    if (!End(tree_of_End))
    {
        return false;
    }
    //��������� ������ � Program
    Tree.addSon("End", "Program", Tree.get_our_root());
    Tree.insert_new_subtree(tree_of_End, "End", Tree.get_our_root());

    //��������, ��� �� ����� �� ����� ����� � ��������� ���������� � ��� ����� None
    bool flag = false;
    if (lex.add_new_unique_value(in, table).name == "None")
    {
        flag = true;
    }
    return flag;
}
//�������, ������� ���������� �������� True ��� False, � ����������� �� ������ ������ Begin
bool syntax_analis::Begin(Tree_of_syntax& Tree)
{
    //��������� ����� �� ������, ���� ��� ����� ������ "�����"
    unique_value value = lex.add_new_unique_value(in, table);

    //���������, ��� ����� ������������� �������
    if (value.name != "PROGRAM")
    {
        cout << "������!\n������� " << value.name << " ��������� Program";
        return 0;
    }
    //������, ��� ����� ����������, ��������� � Begin
    Tree.addSon(value.type + " :  " + value.name , "Begin", Tree.get_our_root());

    //��������� ��������� ����� �� ������, ���� ��� ����� ������ "�����"
    value = lex.add_new_unique_value(in, table);

    //���������, ��� ����� ������������� �������
    if (value.type != "Id")
    {
        cout << "������!\n������� " << value.name << " ��������� Id";
        return 0;
    }
    //������, ��� ����� ����������, ��������� � Begin
    Tree.addSon(value.type + " :  " + value.name , "Begin", Tree.get_our_root());

    //������ ������� ���������, ���������� True
    return 1;
}
bool flag_for_Descr = false;
//�������, ������� ���������� �������� True ��� False, � ����������� �� ������ ������ Descriptions
bool syntax_analis::Descriptions(Tree_of_syntax& Tree)
{
    //��������� ����� �� ������, ���� ��� ����� ������ "�����"
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

    //��������� ����� ��������� 
    Tree_of_syntax subtree_of_descr("Descr");


    if (!Descr(subtree_of_descr))
    {
        return 0;
    }
    flag_for_Descr = true;
    //��������� ��� 
    Tree.insert_child(subtree_of_descr, "Descriptions", Tree.get_our_root());
    Tree_of_syntax buffer("Descriptions");
    Tree.addSon("Descriptions", Tree.get_our_root().get_data(), Tree.get_our_root());
    if (!Descriptions(buffer))
    {
        return 0;
    }
    Tree.insert_new_subtree(buffer, Tree.get_our_root().get_data(), Tree.get_our_root());

    //������ ������� ���������, ���������� True
    return 1;

}
//�������, ������� ���������� �������� True ��� False, � ����������� �� ������ ������ Descr
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

    //������ ������� ���������, ���������� True
    return 1;
}
//�������, ������� ���������� �������� True ��� False, � ����������� �� ������ ������ Type
bool syntax_analis::Type(Tree_of_syntax& Tree)
{
    //��������� ��������� ����� �� ������, ���� ��� ����� ������ "�����"
    unique_value value = lex.add_new_unique_value(in, table);

    //���������, ��� ����� ������������� �������
    if (value.name != "INTEGER" && value.name !="REAL")
    {
        cout << "������!\n������� " << value.name << " ��������� INTEGER ��� REAL";
        return 0;
    }
    Tree.addSon(value.type + " :  " + value.name , Tree.get_our_root().get_data(), Tree.get_our_root());
}
//�������, ������� ���������� �������� True ��� False, � ����������� �� ������ ������ Varlist
bool syntax_analis::Varlist(Tree_of_syntax& Tree)
{
    //��������� ��������� ����� �� ������, ���� ��� ����� ������ "�����"
    unique_value value = lex.add_new_unique_value(in, table);

    //���������, ��� ����� ������������� �������
    if (value.type != "Id")
    {
        cout << "������!\n�������  " << value.name << "   ��������� ID";
        return 0;
    }

    //��������� ���� � Varlist
    Tree.addSon(value.type + " :  " + value.name , "Varlist", Tree.get_our_root());

    //��������� ��������� ����� �� ������, ���� ��� ����� ������ "�����"
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

    //������ ������� ���������, ���������� True
    return 1;
}
bool flag = false;
//�������, ������� ���������� �������� True ��� False, � ����������� �� ������ ������ Operators
bool syntax_analis::Operators(Tree_of_syntax& Tree)
{
    //��������� ��������� ����� �� ������, ���� ��� ����� ������ "�����"
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

    //������ ������� ���������, ���������� True
    return 1;
}
//�������, ������� ���������� �������� True ��� False, � ����������� �� ������ ������ Op
bool syntax_analis::Op(Tree_of_syntax& Tree)
{
    Tree_of_syntax temp;

    //��������� ��������� ����� �� ������, ���� ��� ����� ������ "�����"
    unique_value value = lex.add_new_unique_value(in, table);

    //���������, ��� ����� ������������� �������
    if (value.type == "Id")
    {
        Tree.addSon(value.type + " :  " + value.name , "Op", Tree.get_our_root());
        //��������� ��������� ����� �� ������, ���� ��� ����� ������ "�����"
        value = lex.add_new_unique_value(in, table);

        //���������, ��� ����� ������������� �������
        if (value.name != "=")
        {
            cout << "������!\n������� " << value.name << " ��������� ���� \"=\" ";
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
    //���������, ��� ����� ������������� �������
    else if (value.name == "CALL")
    {
        Tree.addSon(value.type + " :  " + value.name , "Op", Tree.get_our_root());

        //��������� ��������� ����� �� ������, ���� ��� ����� ������ "�����"
        value = lex.add_new_unique_value(in, table);
        if (value.type != "Id")
        {
            cout << "������!\n������� " << value.name << " ��������� Id ";
            return 0;
        }
        Tree.addSon(value.type + " :  " + value.name , "Op", Tree.get_our_root());

        //��������� ��������� ����� �� ������, ���� ��� ����� ������ "�����"
        value = lex.add_new_unique_value(in, table);
        //���������, ��� ����� ������������� �������
        if (value.name != "(")
        {
            cout << "������!\n������� " << value.name << " ��������� ���� ( ";
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

        //��������� ��������� ����� �� ������, ���� ��� ����� ������ "�����"
        value = lex.add_new_unique_value(in, table);

        //���������, ��� ����� ������������� �������
        if (value.name != ")")
        {
            cout << "������!\n������� " << value.name << " ��������� ) ";
            return 0;
        }
        Tree.addSon(value.type + " :  " + value.name , "Op", Tree.get_our_root());

        
    }
    else
    {
        cout << "������!\n������� " << value.name << " ��������� ���������� ��� CALL \n";
        return 0;
    }
    //������ ������� ���������, ���������� True
    return 1;
}
//�������, ������� ���������� �������� True ��� False, � ����������� �� ������ ������ SimpleExpr
bool syntax_analis::SimpleExpr(Tree_of_syntax& Tree)
{
    //��������� ����� �� ������, ���� ��� ����� ������ "�����"
    unique_value value = lex.add_new_unique_value(in, table);

    //���������, ��� ����� ������������� �������
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
        //���������, ��� ����� ������������� �������
        if (value.name != ")")
        {
            cout << "������!\n������� " << value.name << " ��������� )\" ";
            return 0;
        }
    }
    //���������, ��� ����� ������������� �������
    else if (value.type != "Id" && value.type != "int_num" && value.type != "real_num")
    {
        cout << "������!\n������� " << value.name << " ��������� ���� ����� ���� ���������� ";
        return 0;
    }

    //������, ��� ����� ����������, ��������� � SimpleExpr
    Tree.addSon(value.type + " :  " + value.name , "SimpleExpr", Tree.get_our_root());

    //������ ������� ���������, ���������� True
    return 1;
}
//�������, ������� ���������� �������� True ��� False, � ����������� �� ������ ������ Expr
bool syntax_analis::Expr(Tree_of_syntax& Tree)
{
    //C���� ������ ��� SimpleExpr
    Tree_of_syntax buffer("SimpleExpr");

    //���������, ��� ������ ������� ���������
    if (!SimpleExpr(buffer))
    {
        return 0;
    }

    //��������� ������� ��������� ������ � Expr 
    Tree.addSon("SimpleExpr", "Expr", Tree.get_our_root());
    Tree.insert_new_subtree(buffer, "SimpleExpr", Tree.get_our_root());

    //��������� ��������� ����� �� ������, ���� ��� ����� ������ "�����"
    unique_value value = lex.add_new_unique_value(in, table);


    if (value.name != "-" && value.name != "+")
    {
        lex.back_word(in, value.name);
        return 1;
    }

    //������, ��� ����� ����������, ��������� � End
    Tree.addSon(value.type + " :  " + value.name , "Expr", Tree.get_our_root());

    //���������� ����������� ������ 
    if (!Expr(Tree))
    {
        return 0;
    }

    //������ ������� ���������, ���������� True
    return 1;
}

//�������, ������� ���������� �������� True ��� False, � ����������� �� ������ ������ End
bool syntax_analis::End(Tree_of_syntax& Tree)
{
    //��������� ����� �� ������, ���� ��� ����� ������ "�����"
    unique_value value = lex.add_new_unique_value(in, table);

    //���������, ��� ����� ������������� �������
    if (value.name != "END")
    {
        cout << "������!\n������� " << value.name << " �������� END";
        return 0;
    }
    //������, ��� ����� ����������, ��������� � End
    Tree.addSon(value.type + " :  " + value.name , "End", Tree.get_our_root());

    //��������� ��������� ����� �� ������, ���� ��� ����� ������ "�����"
    value = lex.add_new_unique_value(in, table);;

    //���������, ��� ����� ������������� �������
    if (value.type != "Id")
    {
        cout << "������!\n������� " << value.name << " ��������� ����������";
        return 0;
    }
    //������, ��� ����� ����������, ��������� � End
    Tree.addSon(value.type + " :  " + value.name , "End", Tree.get_our_root());

    //������ ������� ���������, ���������� True
    return 1;
}
