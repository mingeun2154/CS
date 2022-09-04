# JDBC

> ### references 🔗   
> DATABASE SYSTEM CONCEPTS ⛵️ 7th edition

## Contents		
* [동적 SQL](https://github.com/mingeun2154/CS/tree/main/DB/JDBC#dynamic-sql)
* [JDBC](https://github.com/mingeun2154/CS/tree/main/DB/JDBC#jdbc-1)
* [DB 접근 과정](https://github.com/mingeun2154/CS/tree/main/DB/JDBC#how-to-use)

#    

## Dynamic SQL
범용 프로그래밍 언어는 함수나 메서드를 사용해서 DB 서버에 접속하고 통신할 수 있다. 

동적 SQL은 프로그램이 **실행 중**에 문자열로 SQL 쿼리를 만들어 제출하고, 결과를 가져올 수 있도록 해준다.

JDBC는Java를 위한 동적 SQL 표준 API를 제공한다.

## JDBC

JDBC 표준은 Java프로그램이 데이터베이스에 접속할 수 있는 API를 정의한다. 즉, DB 시스템과 자바 애플리케이션을 연결하는 인터페이스이다.

JDBC가 제공하는 인터페이스는 `java.sql.*`에 정의되어 있다.

Java에서 데이터베이스로 접근하기 위해서는 JDBC를 지원하는 데이터베이스에 대한 **JDBC Driver**가 필요하다. JDBC Driver는 JDBC 표준이 정의하는 API의 **구현체**이다.

JDBC 드라이버는 데이터베이스에 접속하기 전에 동적으로 메모리에 로드되어야 한다. (gradle같은 툴에 맡긴다)

JDBC의 함수를 호출하면 Dirver에 의해 특정 제품을 위한 호출로 변환된다.

**JDBC는 제품에 대해 독립적이지만 JDBC Driver는 제품에 종속적이다.** 

> 제품에 따라 사용하는 protocol이 다르기 때문에 그 구현체인 Driver가 다른 것이다.

## How to use
JDBC를 사용해 DB에 접근하는 과정은 다음과 같다.

1. Connection 획득(접속 개방) : `getConnection(DB주소, 아이디, 비밀번호)`

2. 데이터베이스 시스템에 SQL Statement 전달 : 두 가지 방식 존재

	* Statement 인스턴스 생성 : **일회용** sql 구문을 생성하고 전달.

	* PreparedStatement 생성 : **재사용이 가능한** sql 구문을 생성.

	> 🚨 특히, 사용자로부터 입력받은 문자열을 쿼리에 사용 할 때에는 PreparedStatement를 이용해야 한다.

3. 예외 및 자원 관리 : `try-with-resources` 구문 사용

4. 쿼리 결과 검색 : `ResultSet` 객체로부터 튜플을 한 개 씩 받아온다.

```Java
public static void JDBCexample(String userid, String passwd) {
	try(Connection conn = DriverManager.getConnection("jdbc:oracle:thin;@db.yale.edu:1521:univdb", userid, passwd);
			Statement stmt = conn.creatStatement();
	) {
		try {
			stmt.executeUpdate(
					"INSERT INTO instructor VALUES('77987', 'Kim', 'Physics', 98000);"
			)
		} catch (SQLException sqle) {
			System.out.println("Could not insert tuple. " + sqle);
		}
		Result rset = stmt.executeQuery(
				"SELECT dept_name, avg(salary) " + 
				"FROM instructor " + 
				"GROUP BY dept_name");
		while (rset.next()) { // 쿼리 결과로 반환된 테이블에서 튜플을 하나씩 가져온다. 더 이상 가져올 게 없으면 false.
			System.out.println(rset.getString("dept_name") + " " + rset.getFloat(2));
		}
	} catch (Exception e) {
		Systemt.out.println("Exception : " + e);
	}
}
```

* `Statement` 객체가 해제되면 `ResultSet` 객체가 암묵적으로 해제된다.

* `rset.getString("dept_name")` : 튜플에서 이름이 dept_name인 속성(열)값을 Java String으로 변환해서 가져온다.

* `rset.getFloat(2)` : 튜플의 2열의 값을 Java Float 객체로 변환해서 가져온다.

	> 속성의 위치를 1부터 센다.
