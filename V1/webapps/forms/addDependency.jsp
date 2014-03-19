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
Proof proof = Proof.get(conn, new Proof.Condition().proofID(proofID)).get(0);
%>

<html>
	<head>
		<meta http-equiv="Content-Type" content="text/html; charset=ISO-8859-1"/>
		<link rel="stylesheet" type="text/css" href="<%=prefix %>/css/default.css"/>
		<script src="<%=prefix %>/javascript/actions.js"></script>
	</head>
	<body>
		<title>StudyAid : <%=proof.getProofForFactRecord().getFactForCourseRecord().getCourseName() %> : <%=proof.getProofForFactRecord().getFactName() %> : <%=proof.getProofName() %> : Add dependency...</title>
		<div class="main">
			<div class="margins">
				<h1>Add dependency...</h1>
				<hr/><br/>
				<form name="addDependency" action="<%=prefix %>/methods/addDependency.jsp" method="get">
					<input type="hidden" name="dependentTo" value="<%=proof.getProofID() %>"/>
					Dependent on:
					<select name="dependentOn">
						<%
						for (Fact fact : proof.getProofForFactRecord().getFactForCourseRecord().getFactsWithFactForCourse())
						{
							%>
							<option value="<%=fact.getFactID() %>"><%=fact.getFactType() %> : <%=fact.getFactName() %></option>
							<%
						}
						%>
					</select>
					<br/><br/>
					<button type="button" style="float: left" onmousedown="goToPage(event, '<%=prefix %>/Proof.jsp?proofID=<%=proof.getProofID() %>')">Cancel</button>
					<button type="submit" style="float: right">Create</button>
				</form>
			</div>
		</div>
	</body>
</html>
