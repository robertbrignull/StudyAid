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

Integer proofForFact = Integer.parseInt(request.getParameter("proofForFact"));

Proof proof = new Proof(conn);

proof.setProofName(request.getParameter("proofName"));
proof.setProofText(request.getParameter("proofText"));
proof.setProofForFact(proofForFact);

proof.create();

response.sendRedirect(prefix + "/Proof.jsp?proofID=" + proof.getProofID());
%>
