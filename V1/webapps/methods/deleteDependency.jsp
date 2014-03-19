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

Integer dependencyID = Integer.parseInt(request.getParameter("dependencyID"));

Dependency dependency = Dependency.get(conn, new Dependency.Condition().dependencyID(dependencyID)).get(0);
dependency.delete();

response.sendRedirect(prefix + "/Proof.jsp?proofID=" + dependency.getDependentTo());
%>
