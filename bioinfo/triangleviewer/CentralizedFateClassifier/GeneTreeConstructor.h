// reconstruct gene tree.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <cinttypes>
#include <cstdlib>
#include <cerrno>
#include <sys/stat.h>
#include <list>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <string>
#include "probabilitiescalculation.h"

//#include <qgraphicsview>
//#include <qtextstream>
//#include <qprocess>
using namespace std;

// =================================================================
//                              Includes
// =================================================================
struct protein {
public:
	int nodeid, id, parent_id;
	long double m, h, w;
	int32_t start_pos_, length_, basal_level_, hamming_dist_;
};

struct Node {
public:
	protein pro;
	bool dup;
	struct Node* left; //Reference to left child
	struct Node* right; //Reference to right child

	Node() { this->left = NULL; this->right = NULL; }

	bool IsLeaf(){
		if (this->left == NULL && this->right == NULL)
			return true;
		else
			return false;
	}

	string GetLabel()
	{
		return to_string(pro.nodeid);
	}

	int GetNbChildren()
	{
		if (this->left != NULL && this->right != NULL)
			return 2;
		else 
			return 1;
	}

	Node* GetChild(int pos)
	{
		if (pos < 0 || pos >= 3)
			throw "Bad child position";
		if(pos == 0)
			return this->left;
		else if (pos == 1)
			return this->right;
	}
};

class GeneTree
{
public:
	//void init(QGraphicsScene* scene, QGraphicsView* view);
	void insert(int a);
	Node* construct_tree(vector<vector<string>> pro_list) {
		vector<Node*> current_level, next_level;
		int numofnodes = 0;
		Node* initial = new Node;
		initial->pro.nodeid = numofnodes;
		numofnodes++;
		initial->dup = false;
		initial->pro.id = stoi(pro_list[0][1]);
		initial->pro.parent_id = stoi(pro_list[0][2]);
		initial->pro.start_pos_ = stoi(pro_list[0][3]);
		initial->pro.length_ = stoi(pro_list[0][4]);
		initial->pro.m = stold(pro_list[0][10]);
		initial->pro.w = stold(pro_list[0][11]);
		initial->pro.h = stold(pro_list[0][12]);
		current_level.push_back(initial);
		int numofpro, i_numofpro = 0;
		//cout << current_level[0]->pro.id<< endl;
		//cout << initial->pro.id << endl;
		//current_level[0]->pro.id = 1;
		//cout << current_level[0]->pro.id << endl;
		//cout << initial->pro.id << endl;
		for (int i = 1; i < pro_list.size(); i++) //pro_list.size()
		{
			if (pro_list[i][0].size() > 1) {
				numofpro = stoi(pro_list[i][8]);
				//cout << "num of pro: " << numofpro << endl;
				i_numofpro = 0;
				Node* next = new Node;
				next->pro.nodeid = numofnodes;
				numofnodes++;
				next->dup = false;
				next->pro.id = stoi(pro_list[i][1]);
				next->pro.parent_id = stoi(pro_list[i][2]);
				next->pro.start_pos_ = stoi(pro_list[i][3]);
				next->pro.length_ = stoi(pro_list[i][4]);
				next->pro.m = stold(pro_list[i][10]);
				next->pro.w = stold(pro_list[i][11]);
				next->pro.h = stold(pro_list[i][12]);
				next_level.push_back(next);
				i_numofpro++;
				//cout << "i_numofpro: " << i_numofpro << endl;
			}
			else if (i_numofpro < numofpro) {
				Node* next = new Node;
				next->pro.nodeid = numofnodes;
				numofnodes++;
				next->dup = false;
				next->pro.id = stoi(pro_list[i][1]);
				next->pro.parent_id = stoi(pro_list[i][2]);
				next->pro.start_pos_ = stoi(pro_list[i][3]);
				next->pro.length_ = stoi(pro_list[i][4]);
				next->pro.m = stold(pro_list[i][10]);
				next->pro.w = stold(pro_list[i][11]);
				next->pro.h = stold(pro_list[i][12]);
				next_level.push_back(next);
				i_numofpro++;
				//cout << "i_numofpro: " << i_numofpro << endl;
			}
			if (i_numofpro == numofpro) {
				for (int n = 0; n < current_level.size(); n++) {
					//cout << "cur at m: " << i << "size: " << current_level.size() << " id:" << current_level[n]->pro.id << " parent id: " << current_level[n]->pro.parent_id << endl;
					for (int m = 0; m < next_level.size(); m++) {
						//cout << "nex at m: " << i << "size: " << next_level.size() << " id:" << next_level[m]->pro.id << " parent id: " << next_level[m]->pro.parent_id << endl;
						if (current_level[n]->pro.id == next_level[m]->pro.parent_id) {
							if (current_level[n]->left == NULL) {
								//cout << current_level[n]->pro.id << " current_level[n]->left is null \n";
								current_level[n]->left = next_level[m];
								//cout << "current_level[n]->left: " << current_level[n]->left->pro.id << "\n";
							}
							else if (current_level[n]->right == NULL) {
								//cout << current_level[n]->pro.id << " current_level[n]->right is null \n";
								current_level[n]->right = next_level[m];
								//cout << "current_level[n]->right: " << current_level[n]->right->pro.id << "\n";
							}
						}
					}
					if (current_level[n]->left != NULL && current_level[n]->right != NULL)
						current_level[n]->dup = true;
				}
				current_level.clear();
				current_level = next_level;
				next_level.clear();
				i_numofpro = 0;
			}
			//cout << "\n";
		}
		return initial;
	}

	void preorderWalk();
	void postorderWalk();
	void inorderWalk();

	void deleteNode(int val);
	void deleteNode(Node* p);
	void show();

	int countNodes();
	int countLevels();
	int countLeftNodes();
	Node* findElem(int val);
protected:
private:
	int countNodes(Node* p);
	int countLevels(Node* p);
	int countLeftNodes(Node* p);

	void preorderWalk(Node* p);
	void postorderWalk(Node* p);
	void inorderWalk(Node* p);

	Node* findSuccessor(int val);

	//QByteArray _prepareGraph();
	//void _graphWalk(Node* p, QTextStream* stream);
	Node* findElem(int val, Node* p);

	Node* _root;
	//QGraphicsScene* _scene;
	//QGraphicsView* _view;
};

struct Trunk
{
	Trunk* prev;
	string str;

	Trunk(Trunk* prev, string str)
	{
		this->prev = prev;
		this->str = str;
	}
};

// Helper function to print branches of the binary tree
void showTrunks(Trunk* p)
{
	if (p == nullptr) {
		return;
	}

	showTrunks(p->prev);
	cout << p->str;
}

void printTree(Node* root, Trunk* prev, bool isLeft)
{
	if (root == nullptr) {
		return;
	}

	string prev_str = "    ";
	Trunk* trunk = new Trunk(prev, prev_str);

	printTree(root->right, trunk, true);

	if (!prev) {
		trunk->str = "---";
	}
	else if (isLeft)
	{
		trunk->str = ".---";
		prev_str = "   |";
	}
	else {
		trunk->str = "`---";
		prev->str = prev_str;
	}

	showTrunks(trunk);
	cout << " " << root->pro.nodeid << endl;

	if (prev) {
		prev->str = prev_str;
	}
	trunk->str = "   |";

	printTree(root->left, trunk, false);
}

void ReturnLeafNodes(Node* root, vector<protein>& leaflist)
{
	// if node is null, return
	if (!root)
		return;

	// if node is leaf node, print its data   
	if (!root->left && !root->right)
	{
		//cout << root->data << " ";
		leaflist.push_back(root->pro);
		return;
	}

	// if left child exists, check for leaf
	// recursively
	if (root->left)
		ReturnLeafNodes(root->left, leaflist);

	// if right child exists, check for leaf
	// recursively
	if (root->right)
		ReturnLeafNodes(root->right, leaflist);
}

void WriteNodeChildren(string& str, Node* curNode, bool addBranchLengthToLabel, bool addInternalNodesLabel)
{
	if (curNode->IsLeaf())
	{

		str += curNode->GetLabel();

		//if (addBranchLengthToLabel && !curNode->IsRoot())
			//str += ":" + Util::ToString(curNode->GetBranchLength());
	}
	else if(curNode->GetNbChildren() > 1)
	{
		str += "(";
		for (int i = 0; i < curNode->GetNbChildren(); i++)
		{
			if (i != 0)
				str += ", ";

			Node* child = curNode->GetChild(i);
			WriteNodeChildren(str, child, addBranchLengthToLabel, addInternalNodesLabel);
		}

		str += ")";

		if (addInternalNodesLabel)
			str += curNode->GetLabel();

		//if (addBranchLengthToLabel && !curNode->IsRoot())
			//str += ":" + Util::ToString(curNode->GetBranchLength());
	}
	else if (curNode->GetNbChildren() == 1) {
		Node* child = curNode->GetChild(0);
		WriteNodeChildren(str, child, addBranchLengthToLabel, addInternalNodesLabel);
	}

}

string ToNewickString(Node* root, bool addBranchLengthToLabel, bool addInternalNodesLabel)
{
	string str;
	WriteNodeChildren(str, root, addBranchLengthToLabel, addInternalNodesLabel);
	str += ";";
	return str;
}

void ClassifyDuplicationFates(Node* root, ofstream& dups_list_file, ofstream& avg_dups_list_file) {
	vector<protein> left_leaflist;
	vector<protein> right_leaflist;
	if (!root)
		return;

	vector<float> fates_probablities;
	fates_probablities.resize(13);
	double sub_avg, cons_avg, new_avg, pseudo_avg, spec_avg;
	int numofleaves;

	if (root->dup == true) {
		if (root->left != nullptr) {
			ReturnLeafNodes(root->left, left_leaflist);
			if (left_leaflist.size() == 0)
				left_leaflist.push_back(root->left->pro);
		}
		if (root->right != nullptr) {
			ReturnLeafNodes(root->right, right_leaflist);
			if (right_leaflist.size() == 0)
				right_leaflist.push_back(root->right->pro);
		}

		float g[3] = { root->pro.m, root->pro.h, root->pro.w };
		/*cout << endl << "node: " << root->pro.nodeid << endl;
		cout << "left_leaves: ";
		for (int i = 0; i < left_leaflist.size(); i++)
			cout << left_leaflist[i].nodeid << "  ";
		cout << "right_leaves: ";
		for (int i = 0; i < right_leaflist.size(); i++)
			cout << right_leaflist[i].nodeid << "  ";
		*/
		/*if (left_leaflist.size() == 1 && right_leaflist.size() == 1 && root->left == nullptr && root->right == nullptr) {
			// m, h, w
			float a[3] = { leaflist[0].m, leaflist[0].h, leaflist[0].w };
			float b[3] = { leaflist[1].m, leaflist[1].h, leaflist[1].w };
			cout << endl;
			fates_probablities = ProbabilitiesCalculation(g, a, b);
			dups_list_file << root->pro.nodeid << "," << g[0] << "," << g[1] << "," << g[2] << ","
				<< leaflist[0].nodeid << "," << a[0] << "," << a[1] << "," << a[2] << ","
				<< leaflist[1].nodeid << "," << b[0] << "," << b[1] << "," << b[2] << ","
				<< fates_probablities[0] << "," << fates_probablities[1] << "," << fates_probablities[2] << "," << fates_probablities[3] << "," << fates_probablities[4] << std::endl;
			//dups_list_file << endl;
			//dups_list_file << "21original node, g.m, g.h, g.w, first descendant id, a.m, a.h, a.w, second descendant id, b.m, b.h, b.w, P_subfunctionlization, P_conservation, P_newfunctionlizatoin, P_pseudogenization, P_specialization " << std::endl;

		}*/
		if (left_leaflist.size() > 0 && right_leaflist.size() > 0){
			numofleaves = left_leaflist.size() * right_leaflist.size();
			sub_avg = 0; cons_avg = 0; new_avg = 0; pseudo_avg = 0; spec_avg = 0;
			for (int i = 0; i < left_leaflist.size() ; i++) {
				float a[3] = { left_leaflist[i].m, left_leaflist[i].h, left_leaflist[i].w };
				for (int j = 0; j < right_leaflist.size(); j++) {
					float b[3] = { right_leaflist[j].m, right_leaflist[j].h, right_leaflist[j].w };
					//cout << endl;
					fates_probablities = ProbabilitiesCalculation(g, a, b);
					sub_avg += fates_probablities[0];
					cons_avg += fates_probablities[1];
					new_avg += fates_probablities[2];
					pseudo_avg += fates_probablities[3];
					spec_avg += fates_probablities[4];
					dups_list_file << root->pro.nodeid << "," << g[0] << "," << g[1] << "," << g[2] << ","
						<< left_leaflist[i].nodeid << "," << a[0] << "," << a[1] << "," << a[2] << ","
						<< right_leaflist[j].nodeid << "," << b[0] << "," << b[1] << "," << b[2] << ","
						<< fates_probablities[0] << "," << fates_probablities[1] << "," << fates_probablities[2] << "," << fates_probablities[3] << "," << fates_probablities[4] << std::endl;
					//dups_list_file << endl;
				}
			}
			avg_dups_list_file << root->pro.nodeid << ","
				<< sub_avg / numofleaves << "," << cons_avg / numofleaves << "," << new_avg / numofleaves << "," << pseudo_avg / numofleaves << "," << spec_avg / numofleaves << std::endl;

		}

	}

	ClassifyDuplicationFates(root->left, dups_list_file, avg_dups_list_file);
	ClassifyDuplicationFates(root->right, dups_list_file, avg_dups_list_file);
}

void WritetoCSV(string proteinlist) {

	vector<vector<string>> content;
	vector<string> row;
	string line, word;
	static std::ofstream dups_list_file("dups_fates_probablities.csv", std::ofstream::trunc);
	dups_list_file << "original node, g.m, g.h, g.w, first descendant id, a.m, a.h, a.w, second descendant id, b.m, b.h, b.w, P_subfunctionlization, P_conservation, P_newfunctionlizatoin, P_pseudogenization, P_specialization " << std::endl;

	static std::ofstream avg_dups_list_file("dups_fates_avg_probablities.csv", std::ofstream::trunc);
	avg_dups_list_file << "original node, P_subfunctionlization, P_conservation, P_newfunctionlizatoin, P_pseudogenization, P_specialization " << std::endl;

	fstream file(proteinlist, ios::in);
	if (file.is_open())
	{
		getline(file, line);
		while (getline(file, line))
		{
			row.clear();

			stringstream str(line);

			while (getline(str, word, ','))
				row.push_back(word);
			content.push_back(row);
		}
	}
	else
		cout << "Could not open the file\n";
	GeneTree gt;
	Node* root = gt.construct_tree(content);
	//cout << "left : " << root->left->pro.id <<  " right : \n" ;
	//printTree(root, nullptr, false);
	ClassifyDuplicationFates(root, dups_list_file, avg_dups_list_file);

	std::string newick_string;
	std::ofstream newick("newick.txt");
	newick_string = ToNewickString(root, true, true);
	newick << newick_string;
}
