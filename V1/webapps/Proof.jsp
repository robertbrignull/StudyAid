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

Proof proof = Proof.get(conn, new Proof.Condition().proofID(Integer.parseInt(request.getParameter("proofID")))).get(0);
%>

<html>
	<head>
		<meta http-equiv="Content-Type" content="text/html; charset=ISO-8859-1"/>
		<link rel="stylesheet" type="text/css" href="<%=prefix %>/css/default.css"/>
		<script src="<%=prefix %>/javascript/actions.js"></script>
		<script type="text/javascript" src="<%=prefix %>/MathJax/MathJax.js?config=TeX-AMS-MML_HTMLorMML"></script>
		<script type="text/javascript">
			function displayText()
			{
				document.getElementById("displayedProof").innerHTML = document.getElementById("proofText").value;
				MathJax.Hub.Queue(["Typeset", MathJax.Hub, "displayedProof"]);
				
				document.getElementById("displayedProof").style.display = "block";
				document.getElementById("editableProof").style.display = "none";
			}
			
			function editText()
			{
				document.getElementById("displayedProof").style.display = "none";
				document.getElementById("editableProof").style.display = "block";
			}
			
			window.onload = function()
			{
				displayText();
			}
		</script>
	</head>
	<body>
		<title>StudyAid : <%=proof.getProofForFactRecord().getFactForCourseRecord().getCourseName() %> : <%=proof.getProofForFactRecord().getFactName() %> : <%=proof.getProofName() %></title>
		<div class="main">
			<div class="margins">
				<h1>'<%=proof.getProofForFactRecord().getFactName() %>' statement</h1>
				<hr/><br/>
				<div class="roundedRect">
					<%=proof.getProofForFactRecord().getFactStatement() %>
				</div>
				<br/><hr/>
				<h1>'<%=proof.getProofName() %>' details</h1>
				<hr/><br/>
				<form name="editProof" action="<%=prefix %>/methods/editProof.jsp" method="get">
					<input type="hidden" name="proofID" value="<%=proof.getProofID() %>"/>
					<input type="hidden" name="proofForFact" value="<%=proof.getProofForFact() %>"/>
					Proof name: <input type="text" name="proofName" value="<%=proof.getProofName() %>"/>
					<br/><br/>
					Proof:<br/>
					<button type="button" onclick="displayText()">Display</button>
					<button type="button" onclick="editText()">Edit</button>
					<br/><br/>
					<div class="roundedRect" id="displayedProof"></div>
					<div id="editableProof"><textArea id="proofText" name="proofText" rows="20" cols="70"><%=proof.getProofText() %></textArea></div>
					<br/><br/>
					<%
					List<Dependency> dependencies = Dependency.get(conn, new Dependency.Condition().dependentTo(proof.getProofID()));
					if (dependencies.size() == 0)
					{
						%>
						No dependencies
						<%
					}
					else
					{
						%>
						Dependent on:
						<table class="paddedTable" width="100%">
							<%
							for (Dependency dependency : dependencies)
							{
								%>
								<tr>
									<td class="paddedCell" onmousedown="goToPage(event, '<%=prefix %>/Fact.jsp?factID=<%=dependency.getDependentOn() %>')"><%=dependency.getDependentOnRecord().getFactName() %></td>
									<td><button type="button" onmousedown="confirmAction('<%=prefix %>/methods/deleteDependency.jsp?dependencyID=<%=dependency.getDependencyID() %>')">Delete</button>
								</tr>
								<%
							}
							%>
						</table>
						<%
					}
					%>
					<br/>
					<button type="button" style="float: right" onmousedown="goToPage(event, '<%=prefix %>/forms/addDependency.jsp?proofID=<%=proof.getProofID() %>')">Add dependency</button>
					<br/><br/><br/>
					<button type="button" style="float: left" onmousedown="confirmAction('<%=prefix %>/methods/deleteProof.jsp?proofID=<%=proof.getProofID() %>')">Delete</button>
					<button type="submit" style="float: right">Save</button>
					<br/><br/>
				</form>
				<hr/><br/><br/>
				<button type="button" style="float: left" onmousedown="goToPage(event, '<%=prefix %>/Fact.jsp?factID=<%=proof.getProofForFact() %>')">Back</button>
				<br/>
			</div>
		</div>
	</body>
</html>
