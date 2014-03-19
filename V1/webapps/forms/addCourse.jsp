<%@ page import = "java.util.*" %>
<%@ page import = "java.sql.*" %>

<%@ page import = "StudyAid.Tables.*" %>

<%
Connection conn = (Connection) session.getAttribute("conn");
String prefix = (String) session.getAttribute("prefix");

if (conn == null) {
	Class.forName("com.mysql.jdbc.Driver").newInstance();
	String connectionURL = "jdbc:mysql://localhost:3306/StudyAid";
	conn = DriverManager.getConnection(connectionURL, "root", "mysql");
	session.setAttribute("conn", conn);
}

if (prefix == null) {
	prefix = "http://localhost:8080/StudyAid";
	session.setAttribute("prefix", prefix);
}
%>

<html>
	<head>
		<meta http-equiv="Content-Type" content="text/html; charset=ISO-8859-1"/>
		<link rel="stylesheet" type="text/css" href="<%=prefix %>/css/default.css"/>
		<script src="<%=prefix %>/javascript/actions.js"></script>
	</head>
	<body>
		<title>StudyAid : Add Course...</title>
		<div class="main">
			<div class="margins">
				<h1>Add course...</h1>
				<hr/><br/>
				<form name="addCourse" action="<%=prefix %>/methods/addCourse.jsp" method="get">
					Course name: <input type="text" name="courseName"/>
					<br/><br/>
					<button type="button" style="float: left" onmousedown="goToPage(event, '<%=prefix %>/index.jsp')">Cancel</button>
					<button type="submit" style="float: right">Create</button>
				</form>
			</div>
		</div>
	</body>
</html>
