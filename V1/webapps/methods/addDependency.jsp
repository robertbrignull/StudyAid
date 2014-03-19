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

Dependency dependency = new Dependency(conn);

dependency.setDependentOn(Integer.parseInt(request.getParameter("dependentOn")));
dependency.setDependentTo(Integer.parseInt(request.getParameter("dependentTo")));

dependency.create();

response.sendRedirect(prefix + "/Proof.jsp?proofID=" + request.getParameter("dependentTo"));
%>
