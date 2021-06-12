#include <iostream>
#include <fstream>
#include <string.h>
#include <string>
#include <stdlib.h>
#pragma warning(disable:4996)
using namespace std;

class Page;
class User;
class Post;
class Comment;

class Helper
{
public:
	static char* GetStringFromBuffer(char* str)
	{
		int size = strlen(str);
		char* temp = new char[size + 1];
		for (int i = 0; i < size; i++)
			temp[i] = str[i];
		temp[size] = '\0';
		return temp;
	}

	static char* GetStringFromBuffer(const char* str)
	{
		int size = strlen(str);
		char* temp = new char[size + 1];
		for (int i = 0; i < size; i++){
			temp[i] = str[i];
		}
		temp[size] = '\0';
		return temp;
	}

	static int get_post_int_from_id(char* id)
	{
		int i = 0;
		char* a = &id[4];

		if (*id != '-' && *id != '1')
			i = atoi(a);

		return i;
	}

	static int get_int_from_id(char* id)
	{
		int i = 0;
		char* a = &id[1];

		if (*id != '-' && *id != '1')
			i = atoi(a);

		return i;
	}
};

class Date
{
private:
	int day;
	int month;
	int year;
public:

	Date()
	{
		day = 0;
		month = 0;
		year = 0;
	}

	Date(int d, int m, int y)
	{
		day = d;
		month = m;
		year = y;
	}

	static Date date;

	static void SetCurrentDate(int d, int m, int y)
	{
		date.day = d;
		date.month = m;
		date.year = y;
	}

	void Set_Date(int d, int m, int y)
	{
		day = d;
		month = m;
		year = y;
	}

	static void PrintCurrentDate()
	{
		cout << date.day << " / " << date.month << " / " << date.year << endl;
	}

	void PrintDate()
	{
		cout << "(" << day << " / " << month << " / " << year << ")" << endl;
	}

	static int get_current_day()
	{
		return date.day;
	}

	static int get_current_month()
	{
		return date.month;
	}

	static int get_current_year()
	{
		return date.year;
	}

	int get_day()
	{
		return day;
	}
};

Date Date::date;

class Object
{
private:
	char* ID;
public:
	char* Get_ID()
	{
		return ID;
	}

	void Set_ID(char* id)
	{
		ID = id;
	}

	Object()
	{
		ID = nullptr;
	}

	virtual void PrintListView() = 0;
};

class Comment : public Object
{
private:
	Object* commented_by;
	char* post_id;
	char* description;
public:
	Comment()
	{
		commented_by = nullptr;
		post_id = nullptr;
		description = nullptr;
	}

	void Set_Comment_id(char* id)
	{
		Set_ID(Helper::GetStringFromBuffer(id));
	}

	void Set_Comment_text(char* comment)
	{
		description = Helper::GetStringFromBuffer(comment);
	}

	void Set_Comment_By(Object* id)
	{
		commented_by = id;
	}

	void Set_Post_Id(char* id)
	{
		post_id = id;
	}

	void PrintListView()
	{
		commented_by->PrintListView();
		cout << " wrote : " << description << endl;
	}
};

class Post :public Object
{
private:
	int no_of_likes;
	int no_of_shares;
	char* description;
	Date  date_posted;
	Comment** comments;
	Object** liked_by;
	Object* shared_by;
	int Comment_Number;
public:
	Post()
	{
		no_of_likes = 0;
		no_of_shares = 1;
		description = nullptr;
		liked_by = 0;
		shared_by = 0;
		no_of_likes = 0;
		comments = new Comment * [10];
		for (int i = 0; i < 10; i++)
			comments[i] = 0;
		Comment_Number = 0;
	}

	void set_post(char* id, int x, int y, int z, char* text)
	{
		Set_ID(Helper::GetStringFromBuffer(id));
		date_posted.Set_Date(x, y, z);
		description = Helper::GetStringFromBuffer(text);
	}

	Object** Get_Likers_List()
	{
		return liked_by;
	}

	Object* Get_Sharers_List()
	{
		return shared_by;
	}

	Date Get_Shared_Date()
	{
		return date_posted;
	}

	void Set_Shared_by(Object* a)
	{
		shared_by = a;
	}

	void set_no_of_likes(int j)
	{
		no_of_likes = j;
	}

	void AddLikeBy(Object* ptr)
	{
		if (no_of_likes == 10)
			cout << "a post can not be liked by ore than 10 users" << endl;
		if (liked_by == 0)
			liked_by = new Object * [10];
		liked_by[no_of_likes] = ptr;
		no_of_likes++;
	}

	void Add_Comment(Comment* text)
	{
		if (Comment_Number < 10)
		{
			comments[Comment_Number] = text;
			Comment_Number++;
		}
	}

	void PrintLikedBy()
	{
		if (liked_by != 0)
		{
			for (int i = 0; i < no_of_likes; i++)
			{
				liked_by[i]->PrintListView();
				cout << endl;
			}
		}
	}

	void PrintComments()
	{
		int i = 0;

		while (comments[i] != nullptr)
		{
			comments[i]->PrintListView();
			i++;
		}
	}

	void print()
	{
		cout << shared_by->Get_ID();
		cout << " ";
		shared_by->PrintListView();
		cout << " shared : ";
		cout << description;
	}

	void PrintPost()
	{
		cout << "____________________________________________________________________________________________________________\n";
		shared_by->PrintListView();
		cout << " shared : ";
		PrintListView();
		cout << "----------------------------------------------------Comments------------------------------------------------\n";
		PrintComments();
		cout << "____________________________________________________________________________________________________________\n\n";
	}

	void PrintListView()
	{
		cout << description;
		cout << "\t";
		date_posted.PrintDate();
	}

	void Print_Likers_List()
	{
		for (int i = 0; i < no_of_likes; i++)
		{
			cout << liked_by[i]->Get_ID() << "--";
			liked_by[i]->PrintListView();
			cout << endl;
		}
	}

	char* Get_Description()
	{
		return description;
	}

	int get_posted_day()
	{
		return date_posted.get_day();
	}
};

class Page :public Object
{
private:
	char* title;
	Post* timeline[10];
	int like_count;
	int no_of_posts;
public:
	Page()
	{
		title = nullptr;
		*timeline = nullptr;
		like_count = 0;
		no_of_posts = 0;
	}

	void Add_Post_In_Timeline(Post* ptr)
	{
		timeline[no_of_posts] = ptr;
		no_of_posts++;
	}

	void Load_Pages(ifstream& fin)
	{
		char buffer[80];

		fin >> buffer;
		Set_ID(Helper::GetStringFromBuffer(buffer));

		fin.getline(buffer, 80);
		title = Helper::GetStringFromBuffer(buffer);
	}

	void PrintListView()
	{
		cout << title;
	}

	char* Get_Title()
	{
		return title;
	}

	void View_Page()
	{
		PrintListView();
		cout << endl;

		for (int i = 0; i < no_of_posts; i++)
			timeline[i]->PrintPost();
	}

	int get_post_count()
	{
		return no_of_posts;
	}

	Post* get_timeline(int j)
	{
		return timeline[j];
	}
};

class User :public Object
{
private:
	char* fName;
	char* sName;
	User** freind_list;
	Page** liked_pages;
	char* freind_id[10];
	char* liked_pages_id[10];
	Post* timeline[10];
	int no_of_liked_pages;
	int no_of_freinds;
	int check_user;
	int check_page;
	int no_of_users;
	int no_of_posts;
public:
	User()
	{
		fName = nullptr;
		sName = nullptr;
		freind_list = nullptr;
		liked_pages = nullptr;
		*timeline = nullptr;
		*freind_id = nullptr;
		*liked_pages_id = nullptr;
		no_of_freinds = 0;
		no_of_liked_pages = 0;
		check_user = 0;
		check_page = 0;
		no_of_users = 0;
		no_of_posts = 0;
	}

	void Add_Post_In_Timeline(Post* ptr)
	{
		timeline[no_of_posts] = ptr;
		no_of_posts++;
	}

	void Load_Users(ifstream& fin)
	{
		char buffer[80];

		fin >> buffer;
		Set_ID(Helper::GetStringFromBuffer(buffer));

		fin >> buffer;
		fName = Helper::GetStringFromBuffer(buffer);

		fin >> buffer;
		sName = Helper::GetStringFromBuffer(buffer);

		int i = 0;
		while (*buffer != '-')
		{
			fin >> buffer;
			freind_id[i] = Helper::GetStringFromBuffer(buffer);
			i++;
		}
		no_of_freinds = i;

		fin >> buffer;

		i = 0;
		while (*buffer != '-')
		{
			liked_pages_id[i] = Helper::GetStringFromBuffer(buffer);
			fin >> buffer;
			i++;
		}
		no_of_liked_pages = i;
	}

	void view_freind_list()
	{
		cout << fName << " " << sName << " -- Freind List" << endl << endl;

		if (no_of_freinds == 1)
			cout << fName << " " << sName << " has 0 freinds" << endl;

		for (int i = 0; i < no_of_freinds - 1; i++)
		{
			cout << freind_list[i]->Get_ID() << "\t--\t";
			freind_list[i]->PrintListView();
			cout << endl;
		}
	}

	void view_liked_pages()
	{
		cout << endl << fName << " " << sName << " -- Liked Pages" << endl << endl;

		if (no_of_liked_pages == 0)
			cout << fName << " " << sName << " has 0 liked pages" << endl;

		for (int i = 0; i < no_of_liked_pages; i++)
		{
			cout << liked_pages[i]->Get_ID() << "\t--";
			liked_pages[i]->PrintListView();
			cout << endl;
		}

		cout << endl;
	}

	void add_freind(User* ptr)
	{
		if (check_user == 0)
			freind_list = new User * [no_of_freinds];
		freind_list[check_user] = ptr;
		check_user++;
	}

	void add_page(Page* ptr)
	{
		if (check_page == 0)
			liked_pages = new Page * [no_of_liked_pages];
		liked_pages[check_page] = ptr;
		check_page++;
	}

	int get_no_of_freinds()
	{
		return no_of_freinds;
	}

	int get_no_of_liked_pages()
	{
		return no_of_liked_pages;
	}

	char* GetFname()
	{
		return fName;
	}

	char* GetSname()
	{
		return sName;
	}

	char** get_freind_id()
	{
		return freind_id;
	}

	char** get_pages_id()
	{
		return liked_pages_id;
	}

	void PrintListView()
	{
		cout << fName << " " << sName;
	}

	void Print_User()
	{
		PrintListView();
		view_freind_list();
		cout << endl;
		view_liked_pages();
	}

	void Prnt_User_Timeline()
	{
		for (int i = 0; i < no_of_posts; i++)
			timeline[i]->PrintPost();
	}

	void View_Home()
	{
		Date d;
		int current_d = d.get_current_day();

		for (int i = 0; i < no_of_freinds - 1; i++)
			for (int j = 0; j < freind_list[i]->no_of_posts; j++)
			{
				int post_d = freind_list[i]->timeline[j]->get_posted_day();
				if (post_d == current_d || post_d == (current_d - 1))
				{
					cout << "____________________________________________________________________________________________________________\n";
					freind_list[i]->PrintListView();
					cout << " shared : " << freind_list[i]->timeline[j]->Get_Description() << endl;
					cout << "------------------------------------------------Comments----------------------------------------------------\n";
					freind_list[i]->timeline[j]->PrintComments();
					cout << "____________________________________________________________________________________________________________\n\n";
				}
			}

		for (int i = 0; i < no_of_liked_pages; i++)
			for (int j = 0; j < liked_pages[i]->get_post_count(); j++)
			{
				int post_d = liked_pages[i]->get_timeline(j)->get_posted_day();
				if (post_d == current_d || post_d == (current_d - 1))
				{
					cout << "____________________________________________________________________________________________________________\n";
					liked_pages[i]->PrintListView();
					cout << " shared : " << liked_pages[i]->get_timeline(j)->Get_Description() << endl;
					cout << "------------------------------------------------Comments----------------------------------------------------\n";
					liked_pages[i]->get_timeline(j)->PrintComments();
					cout << "____________________________________________________________________________________________________________\n\n";
				}
			}
	}
};

class Facebook
{
private:
	User** users;
	Page** pages;
	Post** posts;
	User* current_user;
	Date current_date;
	int no_of_users;
	int no_of_pages;
	int no_of_posts;
	int no_of_comments;
	int post_count_for_sharing;

public:
	Facebook()
	{
		no_of_posts = 0;
		no_of_users = 0;
		no_of_pages = 0;
		no_of_comments = 0;
		users = nullptr;
		pages = nullptr;
		posts = nullptr;
		current_user = nullptr;
		post_count_for_sharing = no_of_posts;
	}

	char identify(char* id)
	{
		return id[0];
	}

	void Set_Current_User(const char* a)
	{
		char* ID = Helper::GetStringFromBuffer(a);
		int id = Helper::get_int_from_id(ID);
		current_user = users[id - 1];

		cout << current_user->GetFname() << " " << current_user->GetSname() << " suucessfully set as current user" << endl << endl;
	}

	void Set_Current_Date(int day, int month, int year)
	{
		current_date.SetCurrentDate(day, month, year);
		current_date.PrintCurrentDate();
	}

	void Users_Load_and_Link(ifstream& fin)
	{
		char buffer[180];

		fin.open("Project-SocialNetworkUers.txt");
		fin >> no_of_users;
		cout << no_of_users << endl;
		fin.getline(buffer, 80);
		users = new User * [no_of_users];
		for (int i = 0; i < no_of_users; i++)
		{
			users[i] = new User;
			users[i]->Load_Users(fin);
		}
		fin.close();

		int index = 0;
		for (int i = 0; i < no_of_users; i++)
		{
			char** freind_ids = users[i]->get_freind_id();
			int no_of_freinds = users[i]->get_no_of_freinds();

			for (int j = 0; j < no_of_freinds; j++)
			{
				if (*freind_ids[j] != '-' && *freind_ids[j] != '1')
					index = Helper::get_int_from_id(freind_ids[j]);
				users[i]->add_freind(users[index - 1]);
			}
		}
		cout << "users loaded" << endl;
	}

	void Pages_Load_and_Link(ifstream& fin)
	{
		char buffer[180];

		fin.open("Project-SocialNetworkPages.txt");
		fin >> no_of_pages;
		fin.getline(buffer, 80);
		pages = new Page * [no_of_pages];
		for (int i = 0; i < no_of_pages; i++)
		{
			pages[i] = new Page;
			pages[i]->Load_Pages(fin);
		}
		fin.close();

		int index = 0;
		for (int i = 0; i < no_of_users; i++)
		{
			char** page_ids = users[i]->get_pages_id();
			int no_of_liked_pages = users[i]->get_no_of_liked_pages();

			for (int j = 0; j < no_of_liked_pages; j++)
			{
				index = Helper::get_int_from_id(page_ids[j]);
				users[i]->add_page(pages[index - 1]);
			}
		}
		cout << "pages loaded" << endl;
	}

	void Posts_Load_and_Link(ifstream& fin)
	{
		int index = 0;
		char check;
		char id[10];
		char text[120];
		char buffer[120];
		int x, y, z;

		fin.open("Project-SocialNetworkPosts.txt");

		fin >> no_of_posts;
		fin.getline(buffer, 80);
		for (int i = 0; i < 6; i++)
			fin.getline(buffer, 80);

		posts = new Post * [no_of_posts];

		for (int i = 0, j = 0; i < no_of_posts; i++)
		{
			posts[i] = new Post;

			Object** Likers = posts[i]->Get_Likers_List();
			Object* Sharers = posts[i]->Get_Sharers_List();

			fin.getline(buffer, 80);
			fin >> id;
			fin >> x;
			fin >> y;
			fin >> z;
			fin.getline(buffer, 120);
			fin.getline(text, 120);

			fin.getline(buffer, 120);
			index = Helper::get_int_from_id(buffer);
			check = identify(buffer);
			if (check == 'u')
			{
				posts[i]->Set_Shared_by(users[index - 1]);
				users[index - 1]->Add_Post_In_Timeline(posts[i]);
			}
			if (check == 'p')
			{
				posts[i]->Set_Shared_by(pages[index - 1]);
				pages[index - 1]->Add_Post_In_Timeline(posts[i]);
			}

			posts[i]->set_post(id, x, y, z, text);

			while (*buffer != '-')
			{
				fin >> buffer;
				if (*buffer == '-' || *buffer == '1')
					Likers = 0;
				else
				{
					index = Helper::get_int_from_id(buffer);
					check = identify(buffer);

					Likers = new Object * [10];

					if (check == 'u')
						posts[i]->AddLikeBy(users[index - 1]);
					if (check == 'p')
						posts[i]->AddLikeBy(pages[index - 1]);
					j++;
				}
			}
			posts[i]->set_no_of_likes(j);
			j = 0;
			fin.getline(buffer, 80);
		}
		fin.close();
		cout << "posts loaded" << endl;
	}

	void Comments_Load_and_Link(ifstream& fin)
	{
		char buffer[180];
		int index = 0;
		char check;
		char id[10];
		char text[180];

		fin.open("Project-SocialNetworkComments.txt");

		fin >> no_of_comments;
		cout << no_of_comments;
		fin.getline(buffer, 180);
		for (int i = 0; i < 2; i++)
			fin.getline(buffer, 180);

		while (!fin.eof())
		{
			Comment* comment = new Comment;

			fin >> id;

			fin >> buffer;
			index = Helper::get_post_int_from_id(buffer);
			if (*buffer != '-' && *buffer != '1')
			{
				posts[index - 1]->Add_Comment(comment);
				comment->Set_Post_Id(buffer);
			}

			fin >> buffer;
			check = identify(buffer);
			index = Helper::get_int_from_id(buffer);
			if (check == 'u')
				comment->Set_Comment_By(users[index - 1]);
			if (check == 'p')
				comment->Set_Comment_By(pages[index - 1]);

			fin.getline(text, 180);

			comment->Set_Comment_id(id);
			comment->Set_Comment_text(text);
		}
		fin.close();
		cout << "comments loaded" << endl;
	}

	void load_and_link()
	{
		ifstream fin;
		Users_Load_and_Link(fin);
		Pages_Load_and_Link(fin);
		Posts_Load_and_Link(fin);
		Comments_Load_and_Link(fin);
		cout << "all loaded" << endl;
	}

	void View_Page(const char* a)
	{
		char* ID = Helper::GetStringFromBuffer(a);
		int id = Helper::get_int_from_id(ID);
		pages[id - 1]->View_Page();
	}

	void View_Post(const char* a)
	{
		char* ID = Helper::GetStringFromBuffer(a);
		int id = Helper::Helper::get_post_int_from_id(ID);
		if (id >= 0 && id < no_of_posts)
		{
			posts[id - 1]->PrintPost();
		}
	}

	void View_Timeline()
	{
		current_user->PrintListView();
		cout << "-- Timeline" << endl;
		current_user->Prnt_User_Timeline();
	}

	void View_liked_by(const char* a)
	{
		cout << "Post Liked By : \n\n";
		char* ID = Helper::GetStringFromBuffer(a);
		int id = Helper::get_post_int_from_id(ID);
		posts[id - 1]->Print_Likers_List();
	}

	void Like_Post(const char* a)
	{
		char* ID = Helper::GetStringFromBuffer(a);
		int id = Helper::get_post_int_from_id(ID);
		posts[id - 1]->AddLikeBy(current_user);
	}

	void Comment_on_Post(const char* a, const char* text)
	{
		char* t = Helper::GetStringFromBuffer(text);
		char* p = Helper::GetStringFromBuffer(a);

		Comment* c = new Comment;
		c->Set_Comment_By(current_user);
		c->Set_Comment_text(t);
		c->Set_Post_Id(p);

		char* ID = Helper::GetStringFromBuffer(a);
		int id = Helper::get_post_int_from_id(ID);
		posts[id - 1]->Add_Comment(c);
	}

	void Search(const char* keyword)
	{
		cout << "\nUsers: \n";
		for (int i = 0; i < no_of_users; i++)
		{
			if (!strcmp((users[i]->GetFname()), keyword))
			{
				cout << "---";
				users[i]->PrintListView();
				cout << endl;
			}

			if (!strcmp((users[i]->GetSname()), keyword))
			{
				cout << "---";
				users[i]->PrintListView();
				cout << endl;
			}
		}

		cout << "\nPosts: \n";
		for (int i = 0; i < no_of_posts; i++)
		{
			if (strstr((posts[i]->Get_Description()), keyword) != NULL)
			{
				cout << "---";
				posts[i]->print();
				cout << endl;
			}
		}

		cout << "\nPages: \n";
		for (int i = 0; i < no_of_pages; i++)
		{
			if (strstr((pages[i]->Get_Title()), keyword) != NULL)
			{
				cout << "---";
				pages[i]->PrintListView();
				cout << endl;
			}
		}
	}

	void Share_Post(const char* a)
	{
		char* ID = Helper::GetStringFromBuffer(a);
		int index = Helper::get_post_int_from_id(ID);

		Post* p = new Post;


		char* id = new char;
		string yoyo = to_string(++post_count_for_sharing);
		char* b = new char[5];
		b[0] = 'p';
		b[1] = 'o';
		b[2] = 's';
		b[3] = 't';
		string s = strcat(b, yoyo.c_str());
		strcpy(id, s.c_str());


		char* text = posts[index - 1]->Get_Description();
		int day = Date::get_current_day();
		int month = Date::get_current_month();
		int year = Date::get_current_year();

		p->Set_Shared_by(current_user);
		p->set_post(id, day, month, year, text);

		current_user->Add_Post_In_Timeline(p);
	}

	void Run()
	{
		load_and_link();
		cout << "...............................................(SET USER & DATE)............................................\n\n";
		Set_Current_Date(15, 11, 2017);
		Set_Current_User("u7");
		cout << "..........................................(FREINDS & LIKED PAGES)...........................................\n\n";
		current_user->view_freind_list();
		current_user->view_liked_pages();
		cout << endl << ".................................................(HOMEPAGE).................................................\n\n";
		current_user->View_Home();
		cout << endl << endl << ".................................................(TIMELINE).................................................\n\n";
		View_Timeline();
		cout << endl << endl << "................................................(LIKED LIST)................................................\n\n";
		View_liked_by("post5");
		cout << endl << endl << ".............................................(ADD LIKE & VIEW)...............................................\n\n";
		Like_Post("post5");
		View_liked_by("post5");
		cout << endl << endl << "............................................(ADD COMMENT & VIEW).............................................\n\n";
		Comment_on_Post("post4", "Good Luck for your Result");
		View_Post("post4");
		Comment_on_Post("post8", "Thanks for the wishes");
		View_Post("post8");
		cout << endl << endl << "............................................(SHARE POST & VIEW)..............................................\n\n";
		Share_Post("post5");
		View_Timeline();
		cout << endl << endl << "................................................(VIEW PAGE).................................................\n\n";
		View_Page("p1");
		cout << endl << endl << ".............................................(SEARCH BIRTHDAY)..............................................\n\n";
		Search("Birthday");
		cout << endl << endl << "................................................(SEARCH ALI)................................................\n\n";
		Search("Ali");
	}
};

int main()
{
	Facebook f;
	f.Run();

	system("pause");
	return 0;
}
