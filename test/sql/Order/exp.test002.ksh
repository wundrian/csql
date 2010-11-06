echo CREATE TABLE Articles ( ArticleID SMALLINT, ArticleTitle CHAR(30) NOT NULL, Copyright INT NOT NULL,PRIMARY KEY(ArticleID));
Statement Executed
echo INSERT INTO Articles VALUES (12786, 'How write a paper',1934);
Statement Executed: Rows Affected = 1
echo INSERT INTO Articles VALUES (13331, 'Publish a paper  ',1919);
Statement Executed: Rows Affected = 1
echo INSERT INTO Articles VALUES (14356, 'Sell a paper     ',1966);
Statement Executed: Rows Affected = 1
echo INSERT INTO Articles VALUES (15729, 'Buy a paper      ',1932);
Statement Executed: Rows Affected = 1
echo INSERT INTO Articles VALUES (16284, 'Conferences      ',1996);
Statement Executed: Rows Affected = 1
echo INSERT INTO Articles VALUES (17695, 'Journal          ',1980);
Statement Executed: Rows Affected = 1
echo INSERT INTO Articles VALUES (19264, 'Information      ',1992);
Statement Executed: Rows Affected = 1
echo INSERT INTO Articles VALUES (19354, 'AI               ',1993);
Statement Executed: Rows Affected = 1
echo CREATE TABLE Authors (AuthID SMALLINT, AuthorFirstName CHAR(20), AuthorMiddleName CHAR(20), AuthorLastName CHAR(20),PRIMARY KEY(AuthID));
Statement Executed
echo INSERT INTO Authors VALUES (1006, 'Henry', 'S.', 'Thompson');
Statement Executed: Rows Affected = 1
echo INSERT INTO Authors VALUES(1007, 'Jason', 'Carol', 'Oak');
Statement Executed: Rows Affected = 1
echo INSERT INTO Authors VALUES(1008, 'James', NULL, 'Elk');
Statement Executed: Rows Affected = 1
echo INSERT INTO Authors VALUES(1009, 'Tom', 'M', 'Ride');
Statement Executed: Rows Affected = 1
echo INSERT INTO Authors VALUES(1010, 'Jack', 'K', 'Ken');
Statement Executed: Rows Affected = 1
echo INSERT INTO Authors VALUES(1011, 'Mary', 'G.', 'Lee');
Statement Executed: Rows Affected = 1
echo INSERT INTO Authors VALUES(1012, 'Annie', NULL, 'Peng');
Statement Executed: Rows Affected = 1
echo INSERT INTO Authors VALUES(1013, 'Alan', NULL, 'Wang');
Statement Executed: Rows Affected = 1
echo INSERT INTO Authors VALUES(1014, 'Nelson', NULL, 'Yin');
Statement Executed: Rows Affected = 1
echo CREATE TABLE AuthorArticle (AuthID SMALLINT NOT NULL, ArticleID SMALLINT NOT NULL,FOREIGN KEY(AuthID) REFERENCES Authors(AuthID), FOREIGN KEY(ArticleID) REFERENCES Articles(ArticleID));
Statement Executed
echo INSERT INTO AuthorArticle VALUES (1006, 14356);
Statement Executed: Rows Affected = 1
echo INSERT INTO AuthorArticle VALUES (1008, 15729);
Statement Executed: Rows Affected = 1
echo INSERT INTO AuthorArticle VALUES (1009, 12786);
Statement Executed: Rows Affected = 1
echo INSERT INTO AuthorArticle VALUES (1010, 17695);
Statement Executed: Rows Affected = 1
echo INSERT INTO AuthorArticle VALUES (1011, 15729);
Statement Executed: Rows Affected = 1
echo INSERT INTO AuthorArticle VALUES (1012, 19264);
Statement Executed: Rows Affected = 1
echo INSERT INTO AuthorArticle VALUES (1012, 19354);
Statement Executed: Rows Affected = 1
echo INSERT INTO AuthorArticle VALUES (1014, 16284);
Statement Executed: Rows Affected = 1
echo SELECT * FROM Articles;
---------------------------------------------------------
	Articles.ArticleID	Articles.ArticleTitle	Articles.Copyright	
---------------------------------------------------------
	12786	How write a paper	1934	
	13331	Publish a paper  	1919	
	14356	Sell a paper     	1966	
	15729	Buy a paper      	1932	
	16284	Conferences      	1996	
	17695	Journal          	1980	
	19264	Information      	1992	
	19354	AI               	1993	
	
echo SELECT * FROM Authors;
---------------------------------------------------------
	Authors.AuthID	Authors.AuthorFirstName	Authors.AuthorMiddleName	Authors.AuthorLastName	
---------------------------------------------------------
	1006	Henry	S.	Thompson	
	1007	Jason	Carol	Oak	
	1008	James	NULL	Elk	
	1009	Tom	M	Ride	
	1010	Jack	K	Ken	
	1011	Mary	G.	Lee	
	1012	Annie	NULL	Peng	
	1013	Alan	NULL	Wang	
	1014	Nelson	NULL	Yin	
	
echo SELECT * FROM AuthorArticle;
---------------------------------------------------------
	AuthorArticle.AuthID	AuthorArticle.ArticleID	
---------------------------------------------------------
	1006	14356	
	1008	15729	
	1009	12786	
	1010	17695	
	1011	15729	
	1012	19264	
	1012	19354	
	1014	16284	
	
echo SELECT ArticleTitle, Copyright FROM Articles  LEFT JOIN AuthorArticle  ON Articles.ArticleID=AuthorArticle.ArticleID LEFT JOIN Authors ON AuthorArticle.AuthID=Authors.AuthID;
---------------------------------------------------------
	ArticleTitle	Copyright	
---------------------------------------------------------
	How write a paper	1934	
	Publish a paper  	1919	
	Sell a paper     	1966	
	Buy a paper      	1932	
	Buy a paper      	1932	
	Conferences      	1996	
	Journal          	1980	
	Information      	1992	
	AI               	1993	
	
echo SELECT ArticleTitle, Copyright FROM Articles  LEFT JOIN AuthorArticle  ON Articles.ArticleID=AuthorArticle.ArticleID LEFT JOIN Authors ON AuthorArticle.AuthID=Authors.AuthID ORDER BY ArticleTitle;
---------------------------------------------------------
	ArticleTitle	Copyright	
---------------------------------------------------------
	AI               	1993	
	Buy a paper      	1932	
	Buy a paper      	1932	
	Conferences      	1996	
	How write a paper	1934	
	Information      	1992	
	Journal          	1980	
	Publish a paper  	1919	
	Sell a paper     	1966	
	
echo DROP table AuthorArticle;
Statement Executed
echo DROP table Authors;
Statement Executed
echo DROP table Articles;
Statement Executed
