//
// Created by jonas on 4/14/2020.
//

#ifndef FINALPROJECT_DOCUMENTPARSER_H
#define FINALPROJECT_DOCUMENTPARSER_H
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/filereadstream.h"
#include "rapidjson/stringbuffer.h"
#include "fstream"
#include "dirent.h"
#include "unistd.h"
#include "sys/stat.h"
#include "sys/types.h"
#include <algorithm>
#include <string>
#include "hashTable.h"
#include "porter2_stemmer.h"
#include "DocumentOBJ.h"
#include "vector"
#include <bits/stdc++.h>
#include "AVLTree.h"
#include "Word.h"
#include "cstring"

using namespace rapidjson;
using namespace std;

class DocumentParser{
private:
    vector<string> formattedAutors;
    string title;
    map<string,int> frequency;
    string paperid;
    string allDocText;
    vector<string> lastname_author;
    vector<Word> vecOfWords;
    vector<string> stopword = {"0o","0s","3a","3b","3d","6b","6o","a","a's","a1","a2","a3","a4","ab","able","about","above","abst","ac","accordance",
                               "according","accordingly","across","act","actually","ad","added","adj","ae","af","affected","affecting","affects","after","afterwards","ag","again","against","ah",
                               "ain","ain't","aj","al","all","allow","allows","almost","alone","along","already","also","although","always","am","among","amongst","amoungst","amount",
                               "an","and","announce","another","any","anybody","anyhow","anymore","anyone","anything","anyway","anyways","anywhere","ao","ap","apart","apparently","appear","appreciate",
                               "appropriate","approximately","ar","are","aren","aren't","arent","arise","around","as","aside","ask","asking","associated","at","au","auth","av","available",
                               "aw","away","awfully","ax","ay","az","b","b1","b2","b3","ba","back","bc","bd","be","became","because","become","becomes",
                               "becoming","been","before","beforehand","begin","beginning","beginnings","begins","behind","being","believe","below","beside","besides","best","better","between","beyond","bi",
                               "bill","biol","bj","bk","bl","bn","both","bottom","bp","br","brief","briefly","bs","bt","bu","but","bx","by","c",
                               "c'mon","c's","c1","c2","c3","ca","call","came","can","can't","cannot","cant","cause","causes","cc","cd","ce","certain","certainly",
                               "cf","cg","ch","changes","ci","cit","cj","cl","clearly","cm","cn","co","com","come","comes","con","concerning","consequently","consider",
                               "considering","contain","containing","contains","corresponding","could","couldn","couldn't","couldnt","course","cp","cq","cr","cry","cs","ct","cu","currently","cv",
                               "cx","cy","cz","d","d2","da","date","dc","dd","de","definitely","describe","described","despite","detail","df","di","did","didn",
                               "didn't","different","dj","dk","dl","do","does","doesn","doesn't","doing","don","don't","done","down","downwards","dp","dr","ds","dt",
                               "du","due","during","dx","dy","e","e2","e3","ea","each","ec","ed","edu","ee","ef","effect","eg","ei","eight",
                               "eighty","either","ej","el","eleven","else","elsewhere","em","empty","en","end","ending","enough","entirely","eo","ep","eq","er","es",
                               "especially","est","et","et-al","etc","eu","ev","even","ever","every","everybody","everyone","everything","everywhere","ex","exactly","example","except","ey",
                               "f","f2","fa","far","fc","few","ff","fi","fifteen","fifth","fify","fill","find","fire","first","five","fix","fj","fl",
                               "fn","fo","followed","following","follows","for","former","formerly","forth","forty","found","four","fr","from","front","fs","ft","fu","full",
                               "further","furthermore","fy","g","ga","gave","ge","get","gets","getting","gi","give","given","gives","giving","gj","gl","go","goes",
                               "going","gone","got","gotten","gr","greetings","gs","gy","h","h2","h3","had","hadn","hadn't","happens","hardly","has","hasn","hasn't",
                               "hasnt","have","haven","haven't","having","he","he'd","he'll","he's","hed","hello","help","hence","her","here","here's","hereafter","hereby","herein",
                               "heres","hereupon","hers","herself","hes","hh","hi","hid","him","himself","his","hither","hj","ho","home","hopefully","how","how's","howbeit",
                               "however","hr","hs","http","hu","hundred","hy","i","i'd","i'll","i'm","i've","i2","i3","i4","i6","i7","i8","ia",
                               "ib","ibid","ic","id","ie","if","ig","ignored","ih","ii","ij","il","im","immediate","immediately","importance","important","in","inasmuch",
                               "inc","indeed","index","indicate","indicated","indicates","information","inner","insofar","instead","interest","into","invention","inward","io","ip","iq","ir","is",
                               "isn","isn't","it","it'd","it'll","it's","itd","its","itself","iv","ix","iy","iz","j","jj","jr","js","jt","ju",
                               "just","k","ke","keep","keeps","kept","kg","kj","km","know","known","knows","ko","l","l2","la","largely","last","lately",
                               "later","latter","latterly","lb","lc","le","least","les","less","lest","let","let's","lets","lf","like","liked","likely","line","little",
                               "lj","ll","ll","ln","lo","look","looking","looks","los","lr","ls","lt","ltd","m","m2","ma","made","mainly","make",
                               "makes","many","may","maybe","me","mean","means","meantime","meanwhile","merely","mg","might","mightn","mightn't","mill","million","mine","miss","ml",
                               "mn","mo","more","moreover","most","mostly","move","mr","mrs","ms","mt","mu","much","mug","must","mustn","mustn't","my","myself",
                               "n","n2","na","name","namely","nay","nc","nd","ne","near","nearly","necessarily","necessary","need","needn","needn't","needs","neither","never",
                               "nevertheless","new","next","ng","ni","nine","ninety","nj","nl","nn","no","nobody","non","none","nonetheless","noone","nor","normally","nos",
                               "not","noted","nothing","novel","now","nowhere","nr","ns","nt","ny","o","oa","ob","obtain","obtained","obviously","oc","od","of",
                               "off","often","og","oh","oi","oj","ok","okay","ol","old","om","omitted","on","once","one","ones","only","onto","oo",
                               "op","oq","or","ord","os","ot","other","others","otherwise","ou","ought","our","ours","ourselves","out","outside","over","overall","ow",
                               "owing","own","ox","oz","p","p1","p2","p3","page","pagecount","pages","par","part","particular","particularly","pas","past","pc","pd",
                               "pe","per","perhaps","pf","ph","pi","pj","pk","pl","placed","please","plus","pm","pn","po","poorly","possible","possibly","potentially",
                               "pp","pq","pr","predominantly","present","presumably","previously","primarily","probably","promptly","proud","provides","ps","pt","pu","put","py","q","qj",
                               "qu","que","quickly","quite","qv","r","r2","ra","ran","rather","rc","rd","re","readily","really","reasonably","recent","recently","ref",
                               "refs","regarding","regardless","regards","related","relatively","research","research-articl","respectively","resulted","resulting","results","rf","rh","ri","right","rj","rl","rm",
                               "rn","ro","rq","rr","rs","rt","ru","run","rv","ry","s","s2","sa","said","same","saw","say","saying","says",
                               "sc","sd","se","sec","second","secondly","section","see","seeing","seem","seemed","seeming","seems","seen","self","selves","sensible","sent","serious",
                               "seriously","seven","several","sf","shall","shan","shan't","she","she'd","she'll","she's","shed","shes","should","should've","shouldn","shouldn't","show","showed",
                               "shown","showns","shows","si","side","significant","significantly","similar","similarly","since","sincere","six","sixty","sj","sl","slightly","sm","sn","so",
                               "some","somebody","somehow","someone","somethan","something","sometime","sometimes","somewhat","somewhere","soon","sorry","sp","specifically","specified","specify","specifying","sq","sr",
                               "ss","st","still","stop","strongly","sub","substantially","successfully","such","sufficiently","suggest","sup","sure","sy","system","sz","t","t's","t1",
                               "t2","t3","take","taken","taking","tb","tc","td","te","tell","ten","tends","tf","th","than","thank","thanks","thanx","that",
                               "that'll","that's","that've","thats","the","their","theirs","them","themselves","then","thence","there","there'll","there's","there've","thereafter","thereby","thered","therefore",
                               "therein","thereof","therere","theres","thereto","thereupon","these","they","they'd","they'll","they're","they've","theyd","theyre","thickv","thin","think","third","this",
                               "thorough","thoroughly","those","thou","though","thoughh","thousand","three","throug","through","throughout","thru","thus","ti","til","tip","tj","tl","tm",
                               "tn","to","together","too","took","top","toward","towards","tp","tq","tr","tried","tries","truly","try","trying","ts","tt","tv",
                               "twelve","twenty","twice","two","tx","u","u201d","ue","ui","uj","uk","um","un","under","unfortunately","unless","unlike","unlikely","until",
                               "unto","uo","up","upon","ups","ur","us","use","used","useful","usefully","usefulness","uses","using","usually","ut","v","va","value",
                               "various","vd","ve","ve","very","via","viz","vj","vo","vol","vols","volumtype","vq","vs","vt","vu","w","wa","want",
                               "wants","was","wasn","wasn't","wasnt","way","we","we'd","we'll","we're","we've","wed","welcome","well","well-b","went","were","weren","weren't",
                               "werent","what","what'll","what's","whatever","whats","when","when's","whence","whenever","where","where's","whereafter","whereas","whereby","wherein","wheres","whereupon","wherever",
                               "whether","which","while","whim","whither","who","who'll","who's","whod","whoever","whole","whom","whomever","whos","whose","why","why's","wi","widely",
                               "will","willing","wish","with","within","without","wo","won","won't","wonder","wont","words","world","would","wouldn","wouldn't","wouldnt","www","x",
                               "x1","x2","x3","xf","xi","xj","xk","xl","xn","xo","xs","xt","xv","xx","y","y2","yes","yet","yj",
                               "yl","you","you'd","you'll","you're","you've","youd","your","youre","yours","yourself","yourselves","yr","ys","yt","z","zero","zi","zz",};


public:
    void parseDocument(string&);
    void tokenization();
    void addStrings(string&a,string&,string&);
    void trimTokens();
    void clearVector();
    void insertIntoAVLTree(AVLTree<Word>&);
    void initialAdditonToAVLTree(AVLTree<Word>&);
    bool findInStopWord(string&);
    void freeMem();
    void stemtrimAuthorNames();
    void deleteAllDocText();
    void initialAuthorInserttoHashTable(hashTable<string,string>&);
    void getDocumentsinDirectory(string&);
    int gettheFrequency();
    void setupVecofWords();
    void insertIntoAVLTreeFromFile(AVLTree<Word>&);
    void createDocOBJ(AVLTree<DocumentOBJ>&);
};


#endif //FINALPROJECT_DOCUMENTPARSER_H
