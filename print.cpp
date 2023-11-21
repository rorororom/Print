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
