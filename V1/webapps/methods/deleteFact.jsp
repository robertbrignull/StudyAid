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

Integer factID = Integer.parseInt(request.getParameter("factID"));

Fact fact = Fact.get(conn, new Fact.Condition().factID(factID)).get(0);

for (Proof proof : fact.getProofsWithProofForFact())
{
	for (Dependency dependency : proof.getDependencysWithDependentTo())
	{
		dependency.delete();
	}
	
	proof.delete();
}

for (Dependency dependency : fact.getDependencysWithDependentOn())
{
	dependency.delete();
}

fact.delete();

response.sendRedirect(prefix + "/Course.jsp?courseID=" + fact.getFactForCourse());
%>
