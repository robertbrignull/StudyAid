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

Fact fact = Fact.get(conn, new Fact.Condition().factID(Integer.parseInt(request.getParameter("factID")))).get(0);
%>

<html>
	<head>
		<meta http-equiv="Content-Type" content="text/html; charset=ISO-8859-1"/>
		<link rel="stylesheet" type="text/css" href="<%=prefix %>/css/default.css"/>
		<script src="<%=prefix %>/javascript/actions.js"></script>
		<script type="text/javascript" src="<%=prefix %>/MathJax/MathJax.js?config=TeX-AMS-MML_HTMLorMML"></script>
		<script type="text/javascript">
			function displayStatement()
			{
				document.getElementById("displayedStatement").innerHTML = document.getElementById("factStatement").value;
				MathJax.Hub.Queue(["Typeset", MathJax.Hub, "displayedStatement"]);
				
				document.getElementById("displayedStatement").style.display = "block";
				document.getElementById("editableStatement").style.display = "none";
			}
			
			function editStatement()
			{
				document.getElementById("displayedStatement").style.display = "none";
				document.getElementById("editableStatement").style.display = "block";
			}
			
			window.onload = function()
			{
				displayStatement();
			}
		</script>
	</head>
	<body>
		<title>StudyAid : <%=fact.getFactForCourseRecord().getCourseName() %> : <%=fact.getFactName() %> : Proofs...</title>
		<div class="main">
			<div class="margins">
				<h1>'<%=fact.getFactName() %>' details</h1>
				<hr/><br/>
				<form name="editFact" action="<%=prefix %>/methods/editFact.jsp" method="get">
					<input type="hidden" name="factID" value="<%=fact.getFactID() %>"/>
					Fact name: <input type="text" name="factName" value="<%=fact.getFactName() %>"/>
					<br/><br/>
					Fact type: <select name="factType">
					<%
					for (FactType factType : FactType.get(conn, null))
					{
						%>
						<option <%=factType.getFactType().equalsIgnoreCase(fact.getFactType()) ? "selected='selected'" : "" %>><%=factType.getFactType() %></option>
						<%
					}
					%>
					</select>
					<br/><br/>
					Fact for course: <select name="factForCourse">
					<%
					for (Course course : Course.get(conn, null))
					{
						%>
						<option value="<%=course.getCourseID() %>" <%=course.getCourseID() == fact.getFactForCourse() ? "selected='selected'" : "" %>><%=course.getCourseName() %></option>
						<%
					}
					%>
					</select>
					<br/><br/>
					Ordering: <input type="text" name="factOrder" value="<%=fact.getFactOrder() %>"/>
					<br/><br/>
					Statement:<br/>
					<button type="button" onclick="displayStatement()">Display</button>
					<button type="button" onclick="editStatement()">Edit</button>
					<br/><br/>
					<div class="roundedRect" id="displayedStatement"></div>
					<div id="editableStatement"><textArea id="factStatement" name="factStatement" rows="10" cols="70"><%=fact.getFactStatement() %></textArea></div>
					<br/><br/>
					<button type="button" style="float: left" onmousedown="confirmAction('<%=prefix %>/methods/deleteFact.jsp?factID=<%=fact.getFactID() %>')">Delete</button>
					<button type="submit" style="float: right">Save</button>
					<br/><br/>
				</form>
				<%
				if (fact.getFactTypeRecord().getFactTypeCanHaveProof() != 0)
				{
					%>
					<hr/><br/>
					<h1>'<%=fact.getFactName() %>' proofs...</h1>
					<hr/>
					<table class="paddedTable" width="100%">
						<%
						List<Proof> proofs = fact.getProofsWithProofForFact();
						
						if (proofs.size() == 0)
						{
							%>
							<tr><td class="paddedCell"><h3>No proofs</h3></td></tr>
							<%
						}
						else
						{
							for (Proof proof : proofs)
							{
								%>
								<tr>
									<td onmousedown="goToPage(event, '<%=prefix %>/Proof.jsp?proofID=<%=proof.getProofID() %>')">
										<h3><%=proof.getProofName() %></h3>
										<div class="roundedRect"><%=proof.getProofText() %></div>
									</td>
								</tr>
								<%
							}
						}
						%>
					</table>
					<br/><br/>
					<button type="button" style="float: right" onmousedown="goToPage(event, '<%=prefix %>/forms/addProof.jsp?factID=<%=fact.getFactID() %>')">Add proof...</button>
					<%
				}
				%>
				<button type="button" style="float: left" onmousedown="goToPage(event, '<%=prefix %>/Course.jsp?courseID=<%=fact.getFactForCourse() %>&factID=<%=fact.getFactID() %>')">Back</button>
				<br/>
			</div>
		</div>
	</body>
</html>
