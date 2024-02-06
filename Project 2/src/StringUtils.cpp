#include "StringUtils.h"

namespace StringUtils{

std::string Slice(const std::string &str, ssize_t start, ssize_t end) noexcept{
    if (start<0){
        start=str.size()+start;
    }//if start is negative, start from the end
    if (start<0){
        start=0;
    }//if start is still negative, start from the beginning
    if (end<0){
        end=str.size()+end;
    }//if end is negative, end from the end
    if (end<0){
        end=0;
    }//if end is still negative, end from the beginning
    if (start>static_cast<ssize_t>(str.size())){
        start=str.size();
    }//if start is greater than the size of the string, start from the end
    if (end>static_cast<ssize_t>(str.size())){
        end=str.size();
    }//if end is greater than the size of the string, end from the end
    if (end==0){
        end=str.size();
    }//if end is 0, end from the end
    if (start>=end){
        return "";
    }//if start is greater than or equal to end, return nothing
    std::string sub;
    for (int i=start;i<end;i++){
        sub=sub+str[i];
    }//for each character in the string, add it to the substring
    return sub;
}

std::string Capitalize(const std::string &str) noexcept{
    std::string cap;
    cap=str;
    cap.front()=toupper(cap.front());
    for (int i=1;i<static_cast<int>(cap.size());i++){
        cap[i]=tolower(cap[i]);
    }//add as capitalized string
    return cap;
}

std::string Upper(const std::string &str) noexcept{
    std::string up;
    for (int i=0;i<static_cast<ssize_t>(str.size());i++){
        up=up+std::to_string(toupper(str[i]));
    }//add as uppercase string
    return up;
}

std::string Lower(const std::string &str) noexcept{
    std::string low;
    for (int i=0;i<static_cast<ssize_t>(str.size());i++){
        low=low+std::to_string(tolower(str[i]));
    }//add as lowercase string
    return low;
}

std::string LStrip(const std::string &str) noexcept{
    std::string ls;
    int i=0;
    while (str[i]==' '){
        i++;
    }
    for (int j=i;j<static_cast<ssize_t>(str.size());j++){
        ls=ls+str[j];
    }
    return ls;
}//remove the left white spaces and return

std::string RStrip(const std::string &str) noexcept{
    std::string rs;
    int i=str.size()-1;
    while (str[i]==' '){
        i--;
    }
    for (int j=0;j<=i;j++){
        rs=rs+str[j];
    }
    return rs;
}//remove the right white spaces and return

std::string Strip(const std::string &str) noexcept{
    std::string st;
    int i=0;
    while (str[i]==' '){
        i++;
    }
    int j=str.size()-1;
    while (str[j]==' '){
        j--;
    }
    for (int k=i;k<=j;k++){
        st=st+str[k];
    }
    return st;
}//remove the left and right white spaces and return

std::string Center(const std::string &str, int width, char fill) noexcept{
    std::string cen;
    if (width<=static_cast<ssize_t>(str.size())){
        return cen;
    }
    else{
        int space=width-str.size();
        int left=space/2;
        int right=space-left;
        cen.insert(0,left,fill);
        cen.append(right,fill);
    }
    return cen;
}//add fill on both sides

std::string LJust(const std::string &str, int width, char fill) noexcept{
    std::string lj;
    if (width<=static_cast<ssize_t>(str.size())){
        return lj;
    }
    else{
        int space=width-str.size();
        lj.insert(0,space,fill);
    }
    return lj;
}//add fill on the left

std::string RJust(const std::string &str, int width, char fill) noexcept{
    std::string rj;
    if (width<=static_cast<ssize_t>(str.size())){
        return rj;
    }
    else{
        int space=width-str.size();
        rj.append(space,fill);
    }
    return rj;
}//add fill on the right

std::string Replace(const std::string &str, const std::string &old, const std::string &rep) noexcept{
    std::string repl=str;
    auto pos=repl.find(old);
    while (pos!=std::string::npos){
        repl.replace(pos, old.size(), rep);
        pos=repl.find(old, pos+rep.size());
    }//replace the old string with the new string
    return repl;
}

std::vector< std::string > Split(const std::string &str, const std::string &splt) noexcept{
    std::vector< std::string > result;
    std::string spl;
    if (splt.empty()){
        spl=" ";
    }
    else{
        spl=splt;
    }
    auto pos=str.find(spl);
    std::string temp = str;
    while (pos!=std::string::npos){
        result.push_back(temp.substr(0,pos));
        temp.erase(0,pos+spl.size());
        pos=temp.find(spl);
    }//split the string
    return result;
}

std::string Join(const std::string &str, const std::vector< std::string > &vect) noexcept{
    std::string result;
    std::string spl=str;
    for (int i=0; i<static_cast<ssize_t>(vect.size()); i++){
        result=result+vect[i];
        if (i!=static_cast<ssize_t>(vect.size())-1){
            result=result+spl;
        }
    }//join the vector of strings
    return result;
}

std::string ExpandTabs(const std::string &str, int tabsize) noexcept{
    std::string result=str;
    std::string::size_type pos=0;
    while (pos!=std::string::npos){
        pos=result.find("\t");
        if (pos!=std::string::npos){
            result.replace(pos, 1, tabsize-(pos%tabsize), ' ');
        }
    }//replace the tabs with spaces
    return result;
}

int EditDistance(const std::string &left, const std::string &right, bool ignorecase) noexcept{
    int l=left.size();
    int r=right.size();
    int matrix[l+1][r+1];
    for (int i=0; i<=l; i++){
        matrix[i][0]=i;
    }
    for (int j=0; j<=r; j++){
        matrix[0][j]=j;
    }//construct the matrix
    for (int i=1; i<=l; i++){
        for (int j=1; j<=r; j++){
            if (ignorecase){
                if (tolower(left[i-1])==tolower(right[j-1])){
                    matrix[i][j]=matrix[i-1][j-1];
                }
                else{
                    matrix[i][j]=std::min(matrix[i-1][j-1], std::min(matrix[i-1][j], matrix[i][j-1]))+1;
                }
            }
            else{
                if (left[i-1]==right[j-1]){
                    matrix[i][j]=matrix[i-1][j-1];
                }
                else{
                    matrix[i][j]=std::min(matrix[i-1][j-1], std::min(matrix[i-1][j], matrix[i][j-1]))+1;
                }
            }
        }
    }
    return matrix[l][r];
}
}