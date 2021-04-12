/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmbabazi <nmbabazi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 16:55:28 by nmbabazi          #+#    #+#             */
/*   Updated: 2021/04/12 13:18:00 by nmbabazi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
#define MAP_HPP

#include <memory>
#include <iostream>
#include <limits>
#include "pair.hpp"
#include "../../allocator.hpp"
#include "../../utils.hpp"

namespace ft
{
    template < class Key, class T, class Compare = ft::less<Key>, typename Alloc = ft::Allocator<pair<const Key,T> > > //creer l'operation less et pes pairs> class map;
    class map
    {
        public:
///////////////////////typedef//////////////////////////////
			typedef Key									key_type;     
			typedef T									mapped_type;
			typedef pair<const key_type,mapped_type>	value_type;
			typedef Compare								key_compare;
			typedef value_type&							reference;
			typedef const value_type&					const_reference;
			typedef value_type*							pointer;
			typedef const value_type*					const_pointer;
	        typedef ptrdiff_t							difference_type; 
    		typedef size_t								size_type;
			typedef Alloc								allocator_type;
            
        private:
			struct Node
			{
				value_type  data;
				Node        *right;
				Node        *left;
				Node		*parent;
                bool        isleaf(){return (right == NULL && left == NULL);}
				Node		*getprev()
                {
                    Node *ret;
                    if (isleaf() || this->left == NULL)
                    { 
                        ret = this->parent;
                        while (ret->data.first > this->data.first && this->data.first)
                            ret = ret->parent;
                        return (ret); 
                    }
                    else 
                    {
                        ret = this->left;
                        while(ret->right)
                            ret = ret->right;
                        return (ret);
                    }
                }
				Node		*getnext()
                {
                    Node *ret;
                    if (isleaf() || this->right == NULL)
                    {  
                        ret = this->parent;
                        while (ret->data.first < this->data.first && this->data.first)
                            ret = ret->parent;
                        return (ret); 
                    }
                    else 
                    {
                        ret = this->right;
                        while(ret->left)
                            ret = ret->left;
                        return (ret);
                    }
                }
			};

			key_compare	    _comp;
            Node            *_end;
            Node            *_begin;
            Node            *_root;
            allocator_type  _alloc;
            size_type       _size;
            ft::Allocator<Node> _alloc_node; 
        public:	
///////////////////////iterator/////////////////////////////////
 			class MapIterator
            {
                public:
                typedef Node*                           pointeur;
                typedef ptrdiff_t						difference_type;

                MapIterator(pointeur ptr = 0): _ptr(ptr){}
                MapIterator(MapIterator const &cp){_ptr = cp.get_ptr();}
                MapIterator operator=(MapIterator const &cp)
                { 
                    if (this != &cp)
                        this->_ptr = cp.get_ptr();
                    return *this;
                }
                ~MapIterator(){}
                
                value_type		&operator*()const {return _ptr->data;}
                value_type       *operator->()const{return &(operator*());}
                MapIterator	&operator++(){_ptr = _ptr->getnext(); return *this;}
                MapIterator	operator++(int){MapIterator it = *this; ++(*this); return it;}
                MapIterator	&operator--(){ _ptr = _ptr->getprev(); return *this;}
                MapIterator	operator--(int){MapIterator it = *this; --(*this); return it;}
                pointeur        get_ptr()const{return _ptr;}

                bool			operator==(const MapIterator &it){ return _ptr == it.get_ptr();}
                bool			operator!=(const MapIterator &it){ return _ptr != it.get_ptr();}
                
                private:
                    pointeur _ptr; 
            };

            class ConstMapIterator
            {
                public:
                typedef Node*                           pointeur;
                typedef const value_type&                        const_ref;
                typedef const value_type*                        const_pointeur;
                typedef ptrdiff_t						difference_type;

                ConstMapIterator(pointeur ptr = 0): _ptr(ptr){}
                ConstMapIterator(MapIterator const &cp){_ptr = cp.get_ptr();}
                ConstMapIterator operator=(ConstMapIterator const &cp)
                { 
                    if (this != &cp)
                        this->_ptr = cp.get_ptr();
                    return *this;
                }
                ~ConstMapIterator(){}
                
                const_ref		operator*()const {return _ptr->data;}
                value_type       *operator->()const{return &(operator*());}
                ConstMapIterator	&operator++(){_ptr = _ptr->getnext(); return *this;}
                ConstMapIterator	operator++(int){ConstMapIterator it = *this; ++(*this); return it;}
                ConstMapIterator	&operator--(){ _ptr = _ptr->getprev(); return *this;}
                ConstMapIterator	operator--(int){ConstMapIterator it = *this; --(*this); return it;}
                pointeur            get_ptr()const{return _ptr;}
                
                bool			operator==(const ConstMapIterator &it){ return _ptr == it.get_ptr();}
                bool			operator!=(const ConstMapIterator &it){ return _ptr != it.get_ptr();}
                
                private:
                    pointeur _ptr; 
            };

            class MapRIterator
            {
                public:
                typedef Node*                           pointeur;
                typedef ptrdiff_t						difference_type;

                MapRIterator(pointeur ptr = 0): _ptr(ptr){}
                MapRIterator(MapRIterator const &cp){_ptr = cp.get_ptr();}
                MapRIterator(MapIterator const &cp){_ptr = cp.get_ptr()->prev;}
                MapRIterator operator=(MapRIterator const &cp)
                { 
                    if (this != &cp)
                        this->_ptr = cp.get_ptr();
                    return *this;
                }
                ~MapRIterator(){}
                
                value_type		&operator*()const {return _ptr->data;}
                value_type       *operator->()const{return &(operator*());}
                MapRIterator	&operator++(){_ptr = _ptr->getprev(); return *this;}
                MapRIterator	operator++(int){MapRIterator it = *this; ++(*this); return it;}
                MapRIterator	&operator--(){ _ptr = _ptr->getnext(); return *this;}
                MapRIterator	operator--(int){MapRIterator it = *this; --(*this); return it;}
                pointeur        get_ptr()const{return _ptr;}

                bool			operator==(const MapRIterator &it){ return _ptr == it.get_ptr();}
                bool			operator!=(const MapRIterator &it){ return _ptr != it.get_ptr();}
                
                private:
                    pointeur _ptr; 
            };

            class ConstMapRIterator
            {
                public:
                typedef Node*                           pointeur;
                typedef const value_type&                        const_ref;
                typedef const value_type*                        const_pointeur;
                typedef ptrdiff_t						difference_type;

                ConstMapRIterator(pointeur ptr = 0): _ptr(ptr){}
                ConstMapRIterator(MapRIterator const &cp){_ptr = cp.get_ptr();}
                ConstMapRIterator(MapIterator const &cp){_ptr = cp.get_ptr()->prev;}
                ConstMapRIterator operator=(ConstMapRIterator const &cp)
                { 
                    if (this != &cp)
                        this->_ptr = cp.get_ptr();
                    return *this;
                }
                ~ConstMapRIterator(){}
                
                const_ref		operator*()const {return _ptr->data();}
                value_type       *operator->()const{return &(operator*());}
                ConstMapRIterator	&operator++(){ return _ptr->getprev();}
                ConstMapRIterator	operator++(int){ConstMapRIterator it = *this; ++(*this); return it;}
                ConstMapRIterator	&operator--(){return _ptr->getnext();}
                ConstMapRIterator	operator--(int){ConstMapRIterator it = *this; --(*this); return it;}
                pointeur            get_ptr()const{return _ptr;}
                
                bool			operator==(const ConstMapRIterator &it){ return _ptr == it.get_ptr();}
                bool			operator!=(const ConstMapRIterator &it){ return _ptr != it.get_ptr();}
                
                private:
                    pointeur _ptr; 
            };
            
            typedef MapIterator        iterator;
            typedef ConstMapIterator   const_iterator;
            typedef MapRIterator        reverse_iterator;
            typedef ConstMapRIterator   const_reverse_iterator;

///////////////////////constructeur//////////////////////////////
			map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()):_comp(comp), _root(NULL), _alloc(alloc), _size(0)
            {
                _end = new_node(value_type());
                _end->right = NULL;
                _end->left = NULL;
                _begin = new_node(value_type());
                _begin->right = NULL;
                _begin->left = NULL;
            }
			template <class InputIterator>
			map (typename ft::Enable_if<!std::numeric_limits<InputIterator>::is_integer, InputIterator>::type first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()):_comp(comp), _root(NULL), _alloc(alloc), _size(0)
			{
                _end = new_node(value_type());
                _end->right = NULL;
                _end->left = NULL;
                _begin = new_node(value_type());
                _begin->right = NULL;
                _begin->left = NULL;
            }
			map (const map& x):_comp(x._comp), _size(0)
            {
                _end = new_node(value_type());
                _end->right = NULL;
                _end->left = NULL;
                _begin = new_node(value_type());
                _begin->right = NULL;
                _begin->left = NULL;
            }

			~map(){}

			map& operator=(const map& x)
            {
                const_iterator it = x.begin();
                const_iterator rit = x.end();
                insert(it, rit);
                return (*this);
            }
///////////////////////iterator//////////////////////////////
			iterator begin(){return iterator(getBegin(_root));}
			const_iterator begin() const{return const_iterator(getBegin(_root));}
			iterator end(){return iterator(getEnd(_root)->right);}
			const_iterator end() const{return const_iterator(getEnd(_root)->right);}

			reverse_iterator rbegin(){return reverse_iterator(getEnd(_root));}
			const_reverse_iterator rbegin() const{return const_reverse_iterator(getEnd(_root));}
			reverse_iterator rend(){return reverse_iterator(getBegin(_root)->left);}
			const_reverse_iterator rend() const{return const_reverse_iterator(getBegin(_root)->left);}
/////////////////////capacity////////////////////////////////
			bool empty() const{return _size == 0;}
			size_type size() const{return _size;}
			size_type max_size() const{return _alloc_node.max_size();}
/////////////////////acces///////////////////////////////////
			mapped_type& operator[] (const key_type& k)
            {
                value_type pr(k, mapped_type());
			    return insert(pr).first->second;
            }
/////////////////////modifiers///////////////////////////////
			pair<iterator,bool> insert (const value_type& val)
            {
                ft::pair<iterator,bool> ret;

                ret.second = (search_bykey(val.first, _root) == NULL);
                if (ret.second == true)
                    my_insert(val, &_root);
                ret.first = iterator(search_bykey(val.first, _root));
                return ret;
            }
			iterator insert (iterator position, const value_type& val)
            {
                Node *ret;
                if ((ret = search_bykey(val.first, _root)))
                    return iterator(ret);
                ret = my_insert(val, &_root);
                (void)position;
                return iterator(ret);
            }
			template <class InputIterator>
			void insert (typename ft::Enable_if<!std::numeric_limits<InputIterator>::is_integer, InputIterator>::type first, InputIterator last)
            {
                while (first != last)
                {
                    insert(*first);
                    first++;
                }
            }
			void erase (iterator position)
            {
                my_erase(position->first, &_root);
            }
			size_type erase (const key_type& k)
            {
                if (!search_bykey(k, _root))
                    return (0);
                my_erase(k, &_root);
                return (1);
            }
			void erase (iterator first, iterator last)
            {
                while (first != last)
                    erase(first++);
            }
			void swap (map& x);
			void clear();
/////////////////////observer///////////////////////////////        
			key_compare key_comp() const;
			key_compare value_comp() const; ///checker le retour 
/////////////////////operation///////////////////////////////
			iterator find (const key_type& k);
			const_iterator find (const key_type& k) const;
			size_type count (const key_type& k) const;
			iterator lower_bound (const key_type& k);
			const_iterator lower_bound (const key_type& k) const;
			iterator upper_bound (const key_type& k);
			const_iterator upper_bound (const key_type& k) const;
			pair<const_iterator,const_iterator> equal_range (const key_type& k) const;
			pair<iterator,iterator>             equal_range (const key_type& k);
/////////////////////utiles///////////////////////////////
        private:
            Node    *my_insert(value_type val, Node **tree)
            {
                if (!*tree)
                {
                    *tree = new_node(val);
                    (*tree)->parent = NULL;
                    if (!_size)
                    {
                        (*tree)->right = &_end;
                        (*tree)->left = &_begin;
                        _end.parent = *tree;
                        _begin.parent = *tree;
                    }
                    _size++;
                    return *tree;
                }
                if (_comp(val.first, (*tree)->data.first))
                {
                    if ((*tree)->left == NULL)
                    {
                        (*tree)->left = new_node(val);
                        (*tree)->left->parent = *tree;
                        _size++;
                        return (*tree)->left;
                    }
                    if ((*tree)->left == &_begin)
                    {
                        (*tree)->left = new_node(val);
                        (*tree)->left->parent = *tree;
                        (*tree)->left->left = &_begin;
                        _begin.parent = (*tree)->left;
                        _size++;
                        return (*tree)->left;
                    }
                    my_insert(val, &(*tree)->left);
                }
                if (!_comp(val.first, (*tree)->data.first))
                {
                    if ((*tree)->right == NULL)
                    {
                        (*tree)->right = new_node(val);
                        (*tree)->right->parent = *tree;
                        _size++;
                        return (*tree)->right;
                    }
                    if ((*tree)->right == &_end)
                    {
                        
                        (*tree)->right = new_node(val);
                        (*tree)->right->parent = *tree;
                        (*tree)->right->right = &_end;
                        _end.parent = (*tree)->right;
                        _size++;
                        return (*tree)->right;
                    }
                    my_insert(val, &(*tree)->right);
                }
                return (NULL);
            }
            void my_erase(key_type val, Node **tree)
            {
                if (!*tree)
                    return ;
                Node *tmp = search_bykey(val, *tree);
                if (!tmp)
                    return ;
                
                else if (tmp->left == NULL && tmp->right == NULL)
                {
                    if(tmp->parent->right == tmp)
                        tmp->parent->right = NULL;
                    else if(tmp->parent->left == tmp)
                        tmp->parent->left = NULL;
                    else if (!tmp->parent)
                        *tree = NULL;
                    _alloc.destroy(&tmp->data);
                    _alloc_node.deallocate(tmp, 1);
                    tmp = NULL; 
                    _size--;
                    return ;
                }
                else if (tmp->left == NULL)
                {
                    tmp->right->parent = tmp->parent;
                    if(tmp->parent->right == tmp)
                        tmp->parent->right = tmp->right;
                    else if(tmp->parent->left == tmp)
                        tmp->parent->left = tmp->right;
                    else if (!tmp->parent)
                        *tree = tmp->right;
                    std::cout << "key " << tmp->data.first << std::endl;
                    _alloc.destroy(&tmp->data);
                    _alloc_node.deallocate(&(*tmp), 1);
                    tmp = NULL; 
                    _size--;
                    return ;
                }
                else if (tmp->right == NULL)
                {
                    tmp->left->parent = tmp->parent;
                    if(tmp->parent->right == tmp)
                        tmp->parent->right = tmp->left;
                    else if(tmp->parent->left == tmp)
                        tmp->parent->left = tmp->left;
                    else if (!tmp->parent)
                        *tree = tmp->left;
                    _alloc.destroy(&tmp->data);
                    _alloc_node.deallocate(tmp, 1);
                    tmp = NULL; 
                    _size--;
                    return ;
                }
                else if (tmp->left != NULL && tmp->right != NULL)
                {      
                                 
                    Node *temp = getBegin(tmp->right);
                    _alloc.destroy(&tmp->data);
                    _alloc.construct(&tmp->data, temp->data);
                    my_erase(tmp->data.first, &tmp->right);
                }
            }
            Node    *new_node(value_type val)
            {
                Node    *new_node = _alloc_node.allocate(1);
                _alloc.construct(&new_node->data, val);
                new_node->right = NULL;
                new_node->left = NULL;
                return (new_node);
            }
            Node *search_bykey(key_type key, Node *tree)
            {
                if (tree == NULL)
                    return NULL;
                if (tree->data.first == key)
                    return tree;
                if (_comp(key, tree->data.first))
                    return search_bykey(key, tree->left);
                if (!_comp(key, tree->data.first) && tree->data.first != key)
                    return search_bykey(key, tree->right);
                return (NULL);
            }
            Node    *getBegin(Node *tree) const
            {
                if (!tree)
                    return (NULL);
                if (!tree->left || tree->left == &_begin)
                    return (tree);
                else
                    return (getBegin(tree->left));  
            }
            Node    *getEnd(Node *tree) const
            {
                if (!tree)
                    return (NULL);
                if (!tree->right || tree->right == &_end)
                    return tree;
                else
                    return (getEnd(tree->right));  
            }
    };
}

#endif