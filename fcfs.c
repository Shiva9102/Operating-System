#include<stdio.h>
#include<stdlib.h>
struct process
{
    int pid;
    int at;
    int bt;
    int ct;
    int tat;
    int wt;
    struct process *next;
};
struct process * insert(struct process *head,int pid,int at,int bt)
{
    struct process *new = (struct process * )malloc(sizeof(struct process));
    struct process *current = head,*previous = head;
    new->pid = pid;
    new->at = at;
    new->bt = bt;
    new->ct = 0;
    new->tat = 0;
    new->wt = 0;
    new->next = NULL;
    if(head == NULL || new->at < head->at)
    {
        new->next = head;
        head = new;
    }
    else
    {
        while(current!=NULL && at>=(current->at))   
        {
            previous = current;
            current = current->next;
        }
        previous->next = new;
        new->next = current;
    }
    return head;
    free(new);
    free(current);
    free(previous);
}
struct process * completion(struct process *head)
{
    int currentTime = 0;
    struct process *temp = head;
    if(head->at!=0)
    currentTime = head->at;
    while(temp!=NULL)
    {
        temp->ct = currentTime + (temp->bt);
        temp->tat = (temp->ct) - (temp->at);
        temp->wt = (temp->tat) - (temp->bt);
        currentTime = temp->ct;
        temp = temp->next;
    } 
    return head;
}
void display(struct process *head,int n)
{
    printf("Process id   Arrival Time   Burst Time   Completion Time   Turn Around Time   Waiting Time\n");
    struct process *temp = head;
    while(temp!=NULL)
    {
        printf("%5d %14d %14d %14d %14d %14d\n",temp->pid,temp->at,temp->bt,temp->ct,temp->tat,abs(temp->wt));
        temp = temp->next;
    }
    temp = head;
    float awt=0.0f,att=0.0f;
    while(temp!=NULL)
    {
        awt = awt + (temp->wt);
        att = att + (temp->tat);
        temp = temp->next;
    }
    printf("\nAverage Waiting Time = %f\n",(awt/n));
    printf("Average Turn Around Time = %f\n",(att/n));
}
struct process * create(struct process *head,int n)
{
    int i,pid,at,bt;
    for(i=0;i<n;i++)
    {
        printf("Enter details of process %d\n",(i+1));
        printf("Enter process id : ");
        scanf("%d",&pid);
        printf("Enter arrival time : ");
        scanf("%d",&at);
        printf("Enter Burst Time : ");
        scanf("%d",&bt);
        head = insert(head,pid,at,bt);
    }
    return head;
}
void main()
{
    struct process *head = NULL;
    int n;
    printf("Enter number of processes : ");
    scanf("%d",&n);
    head = create(head,n);
    head = completion(head);
    display(head,n);
    free(head);
}