#ifndef REGEX_SEARCH_ENGINE_H
#define REGEX_SEARCH_ENGINE_H

#include <vector>
#include <deque>
#include <iostream>
#include <sstream>
#include <map>
#include <set>
#include <unordered_set>
#include <stack>
#include <algorithm>


static int current_state_id = 0;


class DebugStream : public std::ostream
{
public:
    DebugStream() : std::ostream(&buffer)
    {
#ifdef DEBUG
        rdbuf(std::cout.rdbuf());
#else
        rdbuf(nullptr);
#endif
    }

private:
    std::stringbuf buffer;
};

DebugStream debug;

class StateList;

// A state class that represents a state in the NFA
class State
{
public:
    // Constructor for a state that has a character and two out states
    State(char c, State *out1, State *out2)
    {
        this->is_root = false;
        this->c = c;
        this->out1 = out1;
        this->out1id = out1 != nullptr ? out1->id() : -1;
        this->out2 = out2;
        this->out2id = out2 != nullptr ? out2->id() : -1;
        this->stateid = current_state_id++;
    }

    // Constructor for a state that has a character and one out state
    State(char c, State *out1)
    {
        this->is_root = false;
        this->c = c;
        this->out1 = out1;
        this->out1id = out1 != nullptr ? out1->id() : -1;
        this->out2 = nullptr;
        this->out2id = -1;
        this->stateid = current_state_id++;
    }

    // Constructor for a match state
    State()
    {
        this->is_root = false;
        this->is_match_state = false;
        this->c = 0;
        this->out1 = nullptr;
        this->out1id = -1;
        this->out2 = nullptr;
        this->out2id = -1;
        this->stateid = current_state_id++;
    }

    State(bool is_match_state)
    {
        this->is_root = false;
        this->is_match_state = is_match_state;
        this->c = 0;
        this->out1 = nullptr;
        this->out1id = -1;
        this->out2 = nullptr;
        this->out2id = -1;
        this->stateid = current_state_id++;
    }

    void patch(State *state)
    {
        debug << "Patching state " << this->stateid << " with state " << state->stateid << std::endl;
        if (this->out1 == nullptr)
        {
            this->out1 = state;
            this->out1id = state->id();
        }
        else if (this->out2 == nullptr)
        {
            this->out2 = state;
            this->out2id = state->id();
        }
        else
        {
            this->out1->patch(state);
            this->out2->patch(state);
        }
    }

    void patch(std::vector<State *> states)
    {
        for (int i = 0; i < states.size(); i++)
        {
            this->patch(states[i]);
        }
    }

    bool operator==(const State &rhs) const
    {
        return this->stateid == rhs.stateid;
    }

    bool operator!=(const State &rhs) const
    {
        return this->stateid != rhs.stateid;
    }

    bool accept()
    {
        static std::set<State *> visited;
        if (this->is_match_state)
        {
            return true;
        }
        if (!this->is_epsilon())
        {
            return false;
        }
        if (visited.find(this) != visited.end())
        {
            return false;
        }
        visited.insert(this);
        bool can_transition_to_match = (this->out1 != nullptr && this->out1->accept()) || (this->out2 != nullptr && this->out2->accept());
        bool result = this->is_epsilon() && can_transition_to_match;
        visited.erase(this);
        return result;
    }

    bool is_match(char c) const
    {
        return this->c == c;
    }

    bool is_epsilon() const
    {
        return this->c == 0;
    }

    State *getout1()
    {
        return this->out1;
    }

    State *getout2()
    {
        return this->out2;
    }

    int id() const
    {
        return this->stateid;
    }

    friend std::ostream &operator<<(std::ostream &os, const State &state)
    {
        static int indent = 0;
        for (int i = 0; i < indent; i++)
        {
            os << "  ";
        }

        static std::set<int> visited;

        if (state.is_match_state)
        {
            os << "State (" << state.stateid << ") => Match" << std::endl;
        }
        else if (state.is_epsilon())
        {
            os << "State (" << state.stateid << ") => Epsilon" << std::endl;
        }
        else
        {
            os << "State (" << state.stateid << ") => " << (char)state.c << std::endl;
        }
        if (std::find(visited.begin(), visited.end(), state.stateid) != visited.end())
        {
            return os;
        }
        indent++;
        visited.insert(state.stateid);

        if (state.out1 != nullptr)
        {
            os << *state.out1;
        }
        if (state.out2 != nullptr && state.out2 != state.out1)
        {
            os << *state.out2;
        }

        visited.erase(state.stateid);
        indent--;
        return os;
    }

    ~State()
    {
        static std::unordered_set<int> visited;
        if (visited.find(this->id()) != visited.end())
        {
            return;
        }

        if (visited.empty())
        {
            set_root(true);
        }
        if (is_root)
        {
            visited.clear();
        }

        visited.insert(this->id());
        if (this->out1 != nullptr && visited.find(out1id) == visited.end())
        {
            this->out1->set_root(false);
        }
        if (this->out2 != nullptr && visited.find(out2id) == visited.end())
        {
            this->out2->set_root(false);
        }

        if (out1id != -1 && visited.find(out1id) == visited.end())
        {
            delete this->out1;
        }
        if (out2id != -1 && visited.find(out2id) == visited.end())
        {
            delete this->out2;
        }

        if (is_root)
        {
            visited.clear();
        }
    }
    bool is_match_state;

private:
    void set_root(bool is_root)
    {
        this->is_root = is_root;
    }

    std::unordered_set<State *> collect_states()
    {
        std::unordered_set<State *> visited;
        std::stack<State *> stack;
        stack.push(this);

        debug << "Collecting states " << current_state_id << std::endl;

        while (!stack.empty())
        {
            State *state = stack.top();
            stack.pop();
            if (std::find(visited.begin(), visited.end(), state) != visited.end())
            {
                continue;
            }
            visited.insert(state);
            if (state->out1 != nullptr)
            {
                stack.push(state->out1);
            }
            if (state->out2 != nullptr)
            {
                stack.push(state->out2);
            }
        }
        debug << "Collected " << visited.size() << " states" << std::endl;

        return visited;
    }

    int c;
    State *out1;
    State *out2;
    int stateid, out1id, out2id;
    int is_root;
};

// A state list class that represents a list of states
// This is used to keep track of the states that are currently active in the NFA
class StateList
{
public:
    // Constructor for an empty state list
    StateList() {}

    StateList(State *state)
    {
        this->states.insert(state);
    }

    void addstate(State *state)
    {
        if (!this->has_state(state))
        {
            this->states.insert(state);
        }
    }

    void addstate(std::vector<State *> states)
    {
        for (int i = 0; i < states.size(); i++)
        {
            this->addstate(states[i]);
        }
    }

    void addstate(StateList *stateList)
    {
        this->states.insert(stateList->states.begin(), stateList->states.end());
    }

    bool has_state(State *state)
    {
        return this->states.find(state) != this->states.end();
    }

    void patch(State *state)
    {
        debug << "Patching state " << state->id() << " with " << this->states.size() << " states" << std::endl;
        for (std::set<State *>::iterator it = this->states.begin(); it != this->states.end(); it++)
        {
            (*it)->patch(state);
        }
    }

    friend std::ostream &operator<<(std::ostream &os, const StateList &stateList)
    {
        os << "[ ";
        for (std::set<State *>::iterator it = stateList.states.begin(); it != stateList.states.end(); it++)
        {
            os << (*it)->id() << " ";
        }
        return os << ']';
    }

    std::set<State *> states;
};

// A fragment class that represents a fragment of the NFA
// This is used to keep track of the start and end states of the NFA
class Fragment
{
public:
    Fragment(State *start, StateList *out)
    {
        this->start = start;
        this->out = out;
    }

    Fragment()
    {
        this->start = nullptr;
        this->out = nullptr;
    }

    State *start;
    StateList *out;
};

State *post2nfa(std::string postfix)
{
    std::vector<Fragment> allfrags;
    std::vector<Fragment> stack;
    Fragment e1, e2, e;
    State *state;

    for (int i = 0; i < postfix.size() && postfix[i]; i++)
    {
        debug << postfix[i] << std::endl;
        switch (postfix[i])
        {
        case '.':
            if (stack.size() < 2)
            {
                continue;
            }
            e2 = stack.back();
            stack.pop_back();
            e1 = stack.back();
            stack.pop_back();
            e1.out->patch(e2.start);
            e.start = e1.start;
            e.out = e2.out;
            stack.push_back(e);
            allfrags.push_back(e);
            break;
        case '|':
            if (stack.size() < 2)
            {
                continue;
            }

            e2 = stack.back();
            stack.pop_back();
            e1 = stack.back();
            stack.pop_back();
            state = new State();
            state->patch(e1.start);
            state->patch(e2.start);
            e.start = state;
            e.out = e1.out;
            e.out->addstate(e2.out);
            stack.push_back(e);
            allfrags.push_back(e);
            break;
        case '*':
            if (stack.empty())
            {
                continue;
            }

            e1 = stack.back();
            stack.pop_back();
            state = new State();
            e1.out->patch(state);
            e.start = state;
            state->patch(e1.start);
            e.out = new StateList(state);
            stack.push_back(e);
            allfrags.push_back(e);
            break;
        case '+':
            if (stack.empty())
            {
                continue;
            }

            e1 = stack.back();
            stack.pop_back();
            state = new State();
            state->patch(e1.start);
            e.start = e1.start;
            e.out = e1.out;
            e.out->patch(state);
            stack.push_back(e);
            allfrags.push_back(e);
            break;
        case '?':
            if (stack.empty())
            {
                continue;
            }

            e1 = stack.back();
            stack.pop_back();
            state = new State();
            state->patch(e1.start);
            e.start = state;
            e.out = new StateList(state);
            e.out->addstate(e1.out);
            stack.push_back(e);
            allfrags.push_back(e);
            break;
        default:
            state = new State(postfix[i], nullptr);
            e.start = state;
            e.out = new StateList(state);
            stack.push_back(e);
            allfrags.push_back(e);
            break;
        }
    }

    if (stack.empty())
    {
        std::cerr << "Invalid regex" << std::endl;
        exit(1);
    }

    e = stack.back();
    stack.pop_back();
    e.out->patch(new State(true));

    std::set<uintptr_t> visited;
    for (int i = 0; i < allfrags.size(); i++)
    {
        // delete allfrags[i].out;
        if (visited.find((uintptr_t)allfrags[i].out) == visited.end())
        {
            visited.insert((uintptr_t)allfrags[i].out);
            delete allfrags[i].out;
        }
    }

    if (visited.find((uintptr_t)e.out) == visited.end())
    {
        visited.insert((uintptr_t)e.out);
        delete e.out;
    }
    if (visited.find((uintptr_t)e1.out) == visited.end())
    {
        visited.insert((uintptr_t)e1.out);
        delete e1.out;
    }
    if (visited.find((uintptr_t)e2.out) == visited.end())
    {
        visited.insert((uintptr_t)e2.out);
        delete e2.out;
    }


    return e.start;
}

bool is_operator(char c)
{
    return c == '*' || c == '+' || c == '?' || c == '.' || c == '|' || c == '(' || c == ')';
}

std::string infix2postfix(std::string postfix)
{
    std::string output;
    std::stack<char> operator_stack;
    std::map<char, int> precedence;
    precedence['*'] = 3;
    precedence['+'] = 3;
    precedence['?'] = 3;
    precedence['|'] = 1;
    precedence['.'] = 2;

    // First, go through and insert a '.' between all the non-operator characters
    for (int i = 0; i < postfix.size() && postfix[i]; i++)
    {
        if (!is_operator(postfix[i]) && i > 0 && !is_operator(postfix[i - 1]))
        {
            postfix.insert(i, ".");
        }
    }
    debug << "Infix: " << postfix << std::endl;

    // Now go through and handle parentheses
    // a(b|c) => a.b|c
    // (ab) => a.b
    for (int i = 0; i < postfix.size() && postfix[i]; i++)
    {
        if (postfix[i] == '(' && i > 0 && (!is_operator(postfix[i - 1]) || postfix[i - 1] == ')'))
        {
            postfix.insert(i, ".");
            i++;
        }

        if (i < postfix.size() - 1 && postfix[i] == '*' && !is_operator(postfix[i + 1]))
        {
            postfix.insert(i + 1, ".");
            i++;
        }
        else if (i < postfix.size() - 1 && postfix[i] == '+' && !is_operator(postfix[i + 1]))
        {
            postfix.insert(i + 1, ".");
            i++;
        }
        else if (i < postfix.size() - 1 && postfix[i] == '?' && !is_operator(postfix[i + 1]))
        {
            postfix.insert(i + 1, ".");
            i++;
        }
    }

    debug << "Infix: " << postfix << std::endl;

    for (int i = 0; i < postfix.size() && postfix[i]; i++)
    {
        if (postfix[i] == '(')
        {
            operator_stack.push(postfix[i]);
        }
        else if (postfix[i] == ')')
        {
            while (!operator_stack.empty() && operator_stack.top() != '(')
            {
                output += operator_stack.top();
                operator_stack.pop();
            }
            operator_stack.pop();
        }
        else if (precedence.find(postfix[i]) != precedence.end())
        {
            while (!operator_stack.empty() && precedence[operator_stack.top()] >= precedence[postfix[i]])
            {
                output += operator_stack.top();
                operator_stack.pop();
            }
            operator_stack.push(postfix[i]);
        }
        else
        {
            output += postfix[i];
        }
    }

    while (!operator_stack.empty())
    {
        output += operator_stack.top();
        operator_stack.pop();
    }

    std::cout << "Postfix: " << output << std::endl;

    return output;
}

std::vector<int> match(State *start, std::string s) {
        std:: cout << "match\n";
    std::vector<int> allMatches; // Track all matches, including duplicates
    std::vector<State*> clist, nlist;
    clist.push_back(start);
    int st = 0;
    std:: cout << s << "\n";
    std:: cout << s.size() << "\n";
    for (int i = 0; i < s.size() && s[i]; i++) {
        std::set<State*> visited;
        if(clist.size() == 0)
        {
            clist.push_back(start);   
        }
        for (int j = 0; j < clist.size(); j++) {
            State *state = clist[j];

            if (visited.find(state)!= visited.end()) {
                continue;
            }

            if (state->is_match(s[i])) {
                if (state->getout1()!= nullptr) {
                    nlist.push_back(state->getout1());
                }
                if (state->getout2()!= nullptr) {
                    nlist.push_back(state->getout2());
                }
                allMatches.push_back(i);
            } else if (state->is_epsilon()) {
                visited.insert(state);

                if (state->getout1()!= nullptr) {
                    clist.push_back(state->getout1());
                }
                if (state->getout2()!= nullptr) {
                    clist.push_back(state->getout2());
                }
            }
            else
            {
                st =i;
            }
        }
        visited.clear();

        clist = nlist;
        nlist.clear();
        std:: cout << "match\n";


    }
        std:: cout << "match\n";

    return allMatches;
}


class Regex
{
public:
    Regex(std::string pattern)
    {
        // Is pattern empty?
        if (pattern.empty())
        {
            std::cerr << "Pattern cannot be empty" << std::endl;
            exit(1);
        }

        this->pattern = pattern;
        this->start = post2nfa(infix2postfix(pattern));
        std:: cout << "constructor\n";
    
    }

    std::vector<int> get_matches(std::string content)
    {
        std::cout << "content:" << content << std::endl;
        return ::match(this->start, content);
    }
    Regex(const Regex &other)
    {
        this->pattern = other.pattern;
        this->start = post2nfa(infix2postfix(other.pattern));
    }

    ~Regex()
    {
        debug << "Deleting regex" << std::endl;
        delete this->start;
        debug << "Deleted regex" << std::endl;
    }

    // Copy assignment operator
    Regex &operator=(const Regex &other)
    {
        if (this == &other)
        {
            return *this;
        }

        this->pattern = other.pattern;
        this->start = post2nfa(infix2postfix(other.pattern));
        return *this;
    }

    friend std::ostream &operator<<(std::ostream &os, const Regex &regex)
    {
        return os << *regex.start;
    }

private:
    std::string pattern;
    State *start;
};

#endif