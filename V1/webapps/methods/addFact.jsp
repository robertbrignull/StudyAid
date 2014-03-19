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

Fact fact = new Fact(conn);

fact.setFactName(request.getParameter("factName"));
fact.setFactType(request.getParameter("factType"));
fact.setFactForCourse(Integer.parseInt(request.getParameter("factForCourse")));
fact.setFactOrder(Integer.parseInt(request.getParameter("factOrder")));
fact.setFactStatement(request.getParameter("factStatement"));

fact.create();

response.sendRedirect(prefix + "/Fact.jsp?factID=" + fact.getFactID());
%>
