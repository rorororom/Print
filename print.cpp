void GenerateImage(Tree* tree)
{
    assert(tree);

    FILE* dotFile = fopen("grapth.dot", "w");
    if (dotFile)
    {
        fprintf(dotFile, "digraph tree {\n");
        fprintf(dotFile, "\tnode [shape=Mrecord, style=filled, fillcolor=\"#bba6cd\", color=\"#552d7b\"];\n");

        PrintNodeDump(dotFile, tree->rootTree, "#d5a1a7");

        fprintf(dotFile, "}\n");
        fclose(dotFile);
    }
    else
    {
        printf("Ошибка при открытии файла graph.dot\n");
    }
}

static void PrintNodeDump(FILE* dotFile, Node* node, const char* fillColor)
{
    assert(dotFile);
    assert(node);
    assert(fillColor);

    if (node == NULL)
    {
        return;
    }

    if (node->type == INT)
    {
        fprintf(dotFile, "%d [shape=record, style=\"filled,rounded\", color=\"#552d7b\",\
                          fillcolor=\"%s\", fontsize=14, label=\" %d \"];\n",
                          node, fillColor, node->value);
    }
    else if (node->type == OPERAT)
    {
        char operation = IssuesOperation(node);
        fprintf(dotFile, "%d [shape=record, style=\"filled,rounded\", color=\"#552d7b\",\
                          fillcolor=\"%s\", fontsize=14, label=\" %c \"];\n",
                          node, fillColor, operation);
    }

    if (node->left != NULL)
    {
        fprintf(dotFile, "\t%d -> %d;\n", node, node->left);
        PrintNodeDump(dotFile, node->left, "#6495ed");
    }

    if (node->right != NULL)
    {
        fprintf(dotFile, "\t%d -> %d;\n", node, node->right);
        PrintNodeDump(dotFile, node->right, "#bba6cd");
    }
}

//------------------------------------------------------------------------------------------------//

void PrintNodeConsol(Node* node)
{
    if (node == NULL)
    {
        return;
    }
    if (node->type == INT)
    {
        PrintIntNode(node);
    }
    else
    {
        if (node->parent != NULL)
        {
            PrintParentNorNull(node);
        }
        else
        {
            PrintParentNull(node);
        }
    }
}

void PrintIntNode(Node* node)
{
    PrintNodeConsol(node->left);
    printf("%d ", node->value);
    PrintNodeConsol(node->right);
}

void PrintParentNorNull(Node* node)
{
    int operationParent = CheckingPriorityOperation(node->parent->value);
    int operationNowNode = CheckingPriorityOperation(node->value);

    if (operationParent > operationNowNode)
    {
        printf("( ");
    }

    PrintNodeConsol(node->left);
    char operation = IssuesOperation(node);
    printf("%c ", operation);
    PrintNodeConsol(node->right);

    if (operationParent > operationNowNode)
    {
        printf(") ");
    }
}

void PrintParentNull(Node* node)
{
    PrintNodeConsol(node->left);
    char operation = IssuesOperation(node);
    printf("%c ", operation);
    PrintNodeConsol(node->right);
}


int CheckingPriorityOperation(int operation)
{
    if (operation == ADD || operation == SUB) return 0;
    if (operation == MUL || operation == DIV) return 1;
}
