//
// Created by 邓岩 on 2018/7/23.
//

# include <iostream>
# include <set>
# include <map>
# include <vector>
# include <string>
# include <sstream>
# include <fstream>
# include <algorithm>

using std::cin;
using std::cout;
using std::endl;

class QueryResult{
    friend std::ostream &print(std::ostream &os, const QueryResult &qr);
public:
    QueryResult(const std::string &w,std::shared_ptr<std::set<int>> n,std::shared_ptr<std::vector<std::string>> f): findword(w),lines(n),file(f){}
    std::set<int>::iterator begin() { return lines->begin(); }
    std::set<int>::iterator end() { return lines->end(); }
    std::shared_ptr<std::vector<std::string>> get_file() { return file; }
private:
    std::string findword;
    std::shared_ptr<std::set<int>> lines;
    std::shared_ptr<std::vector<std::string>> file;
};

class TextQuery{
public:
    TextQuery(std::ifstream &infile) : file(new std::vector<std::string>) {
        std::string text;
        while(getline(infile,text))
        {
            file->push_back(text);
            int n = file->size() - 1;
            std::istringstream line(text);
            std::string word;
            while(line >> word)
            {
                auto &lines = wm[word];
                if(!lines)
                {
                    lines.reset(new std::set<int>);
                }
                lines->insert(n);
            }
        }
    }
    QueryResult query(const std::string &word) const
    {
        static std::shared_ptr<std::set<int>> nodata(new std::set<int>);
        auto loc = wm.find(word);
        if(loc == wm.end())
            return QueryResult(word,nodata,file);
        else
            return QueryResult(word,loc->second,file);
    }
private:
    std::shared_ptr<std::vector<std::string>> file;
    std::map<std::string,std::shared_ptr<std::set<int>>> wm;
};

std::ostream &print(std::ostream &os, const QueryResult &qr)
{
    os << qr.findword << " occurs " << qr.lines->size() << " " << "times" << endl;
    for (auto num : *qr.lines) {
        os << "\t(line " << num+1 << ") " << *(qr.file->begin() + num) << endl;
    }
    return os;
}

class Query_base {
    friend class Query;
protected:
    virtual ~Query_base() = default;
private:
    virtual QueryResult eval(const TextQuery&) const = 0;
    virtual std::string rep() const = 0;
};

class Query {
    friend Query operator~( const Query &);
    friend Query operator|( const Query &,const Query &);
    friend Query operator&( const Query &,const Query &);
public:
    Query(const std::string &);
    QueryResult eval(const TextQuery &t) const { return q->eval(t); }
    std::string rep() const { return q->rep(); }
private:
    Query(std::shared_ptr<Query_base> query) : q(query) {}
    std::shared_ptr<Query_base> q;
};

std::ostream &operator<<(std::ostream &os,const Query &query)
{
    return os << query.rep();
}

class WordQuery : public Query_base {
    friend class Query;
    WordQuery(const std::string &s): query_word(s) {}
    QueryResult eval(const TextQuery &t) const override { return t.query(query_word); }
    std::string rep() const override { return query_word; }
    std::string query_word;
};

inline Query::Query(const std::string &s) : q(new WordQuery(s)) {}

class NotQuery : public Query_base {
    friend Query operator~(const Query &);
    NotQuery(const Query &q): query(q) {}
    std::string rep() const override { return "~(" + query.rep() + ")"; }
    QueryResult eval(const TextQuery &) const;
    Query query;
};

inline Query operator~(const Query &operand)
{
    return std::shared_ptr<Query_base>(new NotQuery(operand));
}

QueryResult NotQuery::eval(const TextQuery & text) const {
    auto result = query.eval(text);
    auto ret = std::make_shared<std::set<int>>();
    auto beg = result.begin(), end = result.end();
    auto sz = result.get_file()->size();
    for (size_t n = 0; n != sz; ++n) {
        if (beg == end || *beg != n)
            ret->insert(n);
        else if (beg != end)
            ++beg;
    }
    return QueryResult(rep(),ret,result.get_file());
}

class BinaryQuery : public Query_base {
protected:
    BinaryQuery(const Query &l,const Query &r,std::string s): lhs(l),rhs(r),op(s) {}
    std::string rep() const override { return "(" + lhs.rep() + " " + op + " " + rhs.rep() + ")"; }
    Query lhs,rhs;
    std::string op;
};

class AndQuery : public BinaryQuery {
    friend Query operator&(const Query &,const Query &);
    AndQuery(const Query &l,const Query &r): BinaryQuery(l,r,"&") {}
    QueryResult eval(const TextQuery &) const;
};

inline Query operator&(const Query &l,const Query &r)
{
    return std::shared_ptr<Query_base>(new AndQuery(l,r));
}

QueryResult AndQuery::eval(const TextQuery & text) const
{
    auto left = lhs.eval(text),right = rhs.eval(text);
    auto ret = std::make_shared<std::set<int>>();
    std::set_intersection(left.begin(),left.end(),right.begin(),right.end(),std::inserter(*ret,ret->begin()));
    return QueryResult(rep(),ret,left.get_file());
}

class OrQuery : public BinaryQuery {
    friend Query operator|(const Query &,const Query &);
    OrQuery(const Query &l,const Query &r): BinaryQuery(l,r,"|") {}
    QueryResult eval(const TextQuery &) const override;
};

inline Query operator|(const Query &l,const Query &r)
{
    return std::shared_ptr<Query_base>(new OrQuery(l,r));
}

QueryResult OrQuery::eval(const TextQuery & text) const
{
    auto left = lhs.eval(text),right = rhs.eval(text);
    auto ret = std::make_shared<std::set<int>>(left.begin(),left.end());
    ret->insert(right.begin(),right.end());
    return QueryResult(rep(),ret,left.get_file());
}

int main(void)
{
    std::ifstream infile("/Users/dengyan/countries");
    TextQuery tq(infile);
    Query asia = ~Query("Asia");
    print(cout,asia.eval(tq));
}
