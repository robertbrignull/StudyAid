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

Integer courseID = Integer.parseInt(request.getParameter("courseID"));

List<Course> courses = Course.get(conn, new Course.Condition().courseID(courseID));
if (courses.size() == 1)
{
	Course course = courses.get(0);

	course.setCourseName(request.getParameter("courseName"));
	
	course.update();
}

response.sendRedirect(prefix + "/Course.jsp?courseID=" + request.getParameter("courseID"));
%>

