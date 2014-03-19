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

Integer proofID = Integer.parseInt(request.getParameter("proofID"));

List<Proof> proofs = Proof.get(conn, new Proof.Condition().proofID(proofID));
if (proofs.size() == 1)
{
	Proof proof = proofs.get(0);

	proof.setProofName(request.getParameter("proofName"));
	proof.setProofText(request.getParameter("proofText"));
	proof.setProofForFact(Integer.parseInt(request.getParameter("proofForFact")));

	proof.update();
}

response.sendRedirect(prefix + "/Proof.jsp?proofID=" + request.getParameter("proofID"));
%>
