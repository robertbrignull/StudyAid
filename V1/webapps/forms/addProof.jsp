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
Course course = fact.getFactForCourseRecord();
%>

<html>
	<head>
		<meta http-equiv="Content-Type" content="text/html; charset=ISO-8859-1"/>
		<link rel="stylesheet" type="text/css" href="<%=prefix %>/css/default.css"/>
		<script src="<%=prefix %>/javascript/actions.js"></script>
		<script type="text/javascript" src="<%=prefix %>/MathJax/MathJax.js?config=TeX-AMS-MML_HTMLorMML"></script>
		<script type="text/javascript">
			function displayProof()
			{
				document.getElementById("displayedProof").innerHTML = document.getElementById("proofText").value;
				MathJax.Hub.Queue(["Typeset", MathJax.Hub, "displayedProof"]);
				
				document.getElementById("displayedProof").style.display = "block";
				document.getElementById("editableProof").style.display = "none";
			}
			
			function editProof()
			{
				document.getElementById("displayedProof").style.display = "none";
				document.getElementById("editableProof").style.display = "block";
			}
			
			window.onload = function()
			{
				displayProof();
			}
		</script>
	</head>
	<body>
		<title>StudyAid : <%=course.getCourseName() %> : <%=fact.getFactName() %> : Add proof...</title>
		<div class="main">
			<div class="margins">
				<h1>'<%=fact.getFactName() %>' statement</h1>
				<hr/><br/>
				<div class="roundedRect">
					<%=fact.getFactStatement() %>
				</div>
				<br/><hr/>
				<h1>Add proof for '<%=fact.getFactName() %>'</h1>
				<hr/><br/>
				<form name="addProof" action="<%=prefix %>/methods/addProof.jsp" method="get">
					<input type="hidden" name="proofForFact" value="<%=factID %>"/>
					Proof name: <input type="text" name="proofName"/><br/><br/>
					Proof:<br/>
					<button type="button" onclick="displayProof()">Display</button>
					<button type="button" onclick="editProof()">Edit</button>
					<br/><br/>
					<div class="roundedRect" id="displayedProof"></div>
					<div id="editableProof"><textArea id="proofText" name="proofText" rows="20" cols="70"></textArea></div>
					<br/><br/>
					<button type="button" style="float: left" onmousedown="goToPage(event, '<%=prefix %>/Fact.jsp?factID=<%=fact.getFactID() %>')">Cancel</button>
					<button type="submit" style="float: right">Create</button>
				</form>
			</div>
		</div>
	</body>
</html>
