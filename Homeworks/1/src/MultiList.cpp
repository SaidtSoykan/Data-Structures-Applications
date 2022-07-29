#include <iostream>
#include <string>
#include "MultiList.h"

using namespace std;

MultiList::MultiList()
{
    head=NULL;
    tail=NULL;
}

MultiList::~MultiList()
{
    DateNode* p1 = head;
    DateNode* n1 = head;
    TSiteNode* p2 = NULL;
    TSiteNode* n2 = NULL;

    while(n1!=NULL){
        n2 = n1->get_up();
        p2 = n2->get_up();
        while(n2!=NULL)
        {
            n2 = p2->get_up();
            delete p2;
            p2 = n2;
        }
        n1=p1->get_next();
        delete p1;
        p1=n1;
    }
}



DateNode* MultiList::search_prev_hor(string date)
{
    DateNode* p=head;

    if(date<=head->get_date())
        return NULL;
    else
    {
        while(p->get_next())
        {
            if(p->get_next()->get_date() >= date)
                return p;
            p=p->get_next();
        }
        return p;
    }

}

TSiteNode* MultiList::search_prev_ver(string time,TSiteNode* fnode)
{
    TSiteNode* p=fnode;

    if(!p || time<=p->get_time())
        return NULL;
    else
    {
        while(p->get_up())
        {
            if(p->get_up()->get_time()>=time)
                return p;
            p=p->get_up();
        }
        return p;
    }

}

void MultiList::add_ver(string time,string site_name,DateNode* fnode)
{
    TSiteNode* new_node = new TSiteNode(time,site_name);
    TSiteNode* p = fnode->get_up();
    if(!p) //firstly
    {
        fnode->set_up(new_node);
    }
    else
    {
        TSiteNode* prev = this->search_prev_ver(time,p);
        
        if(prev==NULL) //first node
        {
            new_node->set_up(p);
            fnode->set_up(new_node);
            
        }
        else if(prev->get_up()==NULL) //last node
        {
            prev->set_up(new_node);
        }
        else //between node
        { 
            new_node->set_up(prev->get_up());
            prev->set_up(new_node);
        }
    }
}

void MultiList::delete_ver(string time,DateNode* fnode)
{
    TSiteNode* p = fnode->get_up();
    TSiteNode* prev = this->search_prev_ver(time,p);

    if(!p) //no node
        return;
   
    if(!p->get_up()) //only one node
    {
        delete p;
        fnode->set_up(NULL);
    }
    else
    {
        if(prev==NULL) //first node
        { 
            fnode->set_up(p->get_up());
            p->set_up(NULL);
            delete p;
        }
        else if(prev->get_up()->get_up()==NULL) //last node
        {
            delete prev->get_up();
            prev->set_up(NULL);
        }
        else //between node
        {
            TSiteNode* cur = prev->get_up();
            prev->set_up(cur->get_up());
            cur->set_up(NULL);
            delete cur;
        }
    }
}



void MultiList::add_node(string date,string time,string site_name)
{
    
    if(head==NULL) //firstly
    {
        DateNode* new_hor = new DateNode(date);
        TSiteNode* new_ver = new TSiteNode(time,site_name);
        new_hor->set_up(new_ver);
        head=new_hor;
        tail=new_hor;
    }
    else
    {
        if(head->get_date() == date) // if date already added and equals to head
        {
            this->add_ver(time,site_name,head);
            return;
        }

        DateNode* prev = this->search_prev_hor(date);

        if(prev && prev->get_next() && prev->get_next()->get_date() == date) //date already added and not equal to head
        {
            this->add_ver(time,site_name,prev->get_next());
        }

        else //date not added
        {
            DateNode* new_hor = new DateNode(date);

            if(prev==NULL) //add to beginning
            {
                new_hor->set_next(head);
                head->set_prev(new_hor);
                head=new_hor;
            }
            else if(prev==tail) // add to ending
            {
                tail->set_next(new_hor);
                new_hor->set_prev(tail);
                tail=new_hor;
            }
            else //between
            {
                DateNode* old_next= prev->get_next();
                new_hor->set_next(old_next);
                new_hor->set_prev(prev);
                prev->set_next(new_hor);
                old_next->set_prev(new_hor);
            }
            this->add_ver(time,site_name,new_hor);
        }
    }
}
    

void MultiList::remove_node(string date,string time)
{
    DateNode* prev = this->search_prev_hor(date);
    DateNode* cur;
    if(prev == NULL) //if head
        cur = head;
    else
        cur = prev->get_next();
    this->delete_ver(time,cur);

}

void MultiList::print_list()
{
    DateNode* p_hor=head;
    TSiteNode* p_ver;
    
    while(p_hor)
    {
        cout<<p_hor->get_date()<<":"<<endl;
        p_ver=p_hor->get_up();
        while(p_ver)
        {
            cout<<p_ver->get_time()<<"->"<<p_ver->get_site_name()<<endl;
            p_ver=p_ver->get_up();
        }
        p_hor=p_hor->get_next();
    }

}
