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

Course course = Course.get(conn, new Course.Condition().courseID(Integer.parseInt(request.getParameter("courseID")))).get(0);
%>

<html>
	<head>
		<meta http-equiv="Content-Type" content="text/html; charset=ISO-8859-1"/>
		<link rel="stylesheet" type="text/css" href="<%=prefix %>/css/default.css"/>
		<script src="<%=prefix %>/javascript/actions.js"></script>
		<script type="text/x-mathjax-config">
			MathJax.Hub.Config({
				skipStartupTypeset: true
			});
		</script>
		<script type="text/javascript" src="<%=prefix %>/MathJax/MathJax.js?config=TeX-AMS-MML_HTMLorMML"></script>
		<script type="text/javascript">
			function scrollToFact(n)
			{
				document.getElementById("fact" + n).scrollIntoView(true);
			}
			
			function showHideExtra(n)
			{
				var obj = document.getElementById("extraInfo" + n);
				if (obj.style.display == "none")
				{
					MathJax.Hub.Queue(["Typeset", MathJax.Hub, "extraInfo" + n]);
					obj.style.display = "";
					document.getElementById("showHide" + n).src = "<%=prefix %>/img/arrow_down.png";
				}
				else
				{
					obj.style.display = "none";
					document.getElementById("showHide" + n).src = "<%=prefix %>/img/arrow_left.png";
				}
			}
			
			window.onload = function()
			{
				<%
				String factID = request.getParameter("factID");
				if (factID != null)
				{
					%>
					scrollToFact(<%=factID%>);
					<%
				}
				%>
			}
		</script>
	</head>
	<body>
		<title>StudyAid : <%=course.getCourseName() %> : Facts...</title>
		<div class="main">
			<div class="margins">
				<h1><%=course.getCourseName() %> Details...</h1>
				<hr/><br/>
				<form name="editCourse" action="<%=prefix %>/methods/editCourse.jsp" method="get">
					<input type="hidden" name="courseID" value="<%=course.getCourseID() %>"/>
					Course name: <input type="text" name="courseName" value="<%=course.getCourseName() %>"/>
					<br/><br/>
					<button type="button" style="float: left" onmousedown="confirmAction('<%=prefix %>/methods/deleteCourse.jsp?courseID=<%=course.getCourseID() %>')">Delete</button>
					<button type="submit" style="float: right">Save</button>
					<br/><br/>
				</form>
				<hr/>
				<h1><%=course.getCourseName() %> Facts...</h1>
				<hr/>
				<table>
					<tr>
						<td>Order by:</td>
						<td><button type="button" onmousedown="goToPage(event, '<%=prefix %>/Course.jsp?courseID=<%=request.getParameter("courseID") %>&order=user&limit=<%=request.getParameter("limit") %>')">user ordering</button></td>
						<td><button type="button" onmousedown="goToPage(event, '<%=prefix %>/Course.jsp?courseID=<%=request.getParameter("courseID") %>&order=factType&limit=<%=request.getParameter("limit") %>')">fact type</button></td>
					</tr>
				</table>
				<table>
					<tr>
						<td>Limit to:</td>
						<td><button type="button" onmousedown="goToPage(event, '<%=prefix %>/Course.jsp?courseID=<%=request.getParameter("courseID") %>&order=<%=request.getParameter("order") %>')">all</button></td>
						<td><button type="button" onmousedown="goToPage(event, '<%=prefix %>/Course.jsp?courseID=<%=request.getParameter("courseID") %>&order=<%=request.getParameter("order") %>&limit=proven')">proven</button></td>
						<td><button type="button" onmousedown="goToPage(event, '<%=prefix %>/Course.jsp?courseID=<%=request.getParameter("courseID") %>&order=<%=request.getParameter("order") %>&limit=unproven')">unproven</button></td>
					</td>
				</table>
				<table class="paddedTable" width="100%">
					<%
					List<Fact> facts = null;
					if (course != null)
					{
						facts = course.getFactsWithFactForCourse();
					}
					else
					{
						facts = Fact.get(conn, null);
					}
					
					if (facts.size() == 0)
					{
						%>
						<tr><td class="paddedCell"><h3>No facts</h3></td></tr>
						<%
					}
					else
					{
						String ordering = request.getParameter("order");
						if (ordering == null || ordering.equalsIgnoreCase("null") || ordering.equalsIgnoreCase("user"))
						{
							Collections.sort(facts, new Comparator<Fact>() {
								public int compare(Fact f1, Fact f2) {
									return f1.getFactOrder().compareTo(f2.getFactOrder());
								}
							});
						}
						else if (ordering.equalsIgnoreCase("factType"))
						{
							Collections.sort(facts, new Comparator<Fact>() {
								public int compare(Fact f1, Fact f2) {
									int ord = f1.getFactType().compareTo(f2.getFactType());
									if (ord == 0)
									{
										ord = f1.getFactOrder().compareTo(f2.getFactOrder());
									}
									return ord;
								}
							});
						}
						
						for (Fact fact : facts)
						{
							List<Proof> proofs = fact.getProofsWithProofForFact();
							
							String limit = request.getParameter("limit");
							if (limit == null || limit.equalsIgnoreCase("null")
									|| (limit.equalsIgnoreCase("proven") && proofs.size() > 0)
									|| (limit.equalsIgnoreCase("unproven") && proofs.size() == 0 && fact.getFactTypeRecord().getFactTypeCanHaveProof() != 0))
							{
								%>
								<tr id="fact<%=fact.getFactID() %>">
									<td class="paddedCell" style="background-color: <%=fact.getFactTypeRecord().getFactTypeColour() %>" onmousedown="goToPage(event, '<%=prefix %>/Fact.jsp?factID=<%=fact.getFactID() %>')">
										<%=fact.getFactType() %> : <%=fact.getFactName() %>
									</td>
									<td class="paddedCell" width="10%" onclick="showHideExtra(<%=fact.getFactID() %>)">
										<img id="showHide<%=fact.getFactID() %>" src="<%=prefix %>/img/arrow_left.png" width="25px" height="25%"/>
									</td>
								</tr>
								<tr id="extraInfo<%=fact.getFactID() %>" style="display: none">
									<td class="padded" colspan="2" onmousedown="goToPage(event, '<%=prefix %>/Fact.jsp?factID=<%=fact.getFactID() %>')">
										<div class="roundedRect"><%=fact.getFactStatement() %></div>
										<%
										if (fact.getFactTypeRecord().getFactTypeCanHaveProof() != 0)
										{
											%>
											<p>Number of proofs: <%=proofs.size() %></p>
											<%
										}
										%>
									</td>
								</tr>
								<%
							}
						}
					}
					%>
				</table>
				<br/><br/>
				<button type="button" style="float: left" onmousedown="goToPage(event, '<%=prefix %>/index.jsp')">Back</button>
				<%
				if (course != null)
				{
					%>
					<button type="button" style="float: right" onmousedown="goToPage(event, '<%=prefix %>/forms/addFact.jsp?courseID=<%=course.getCourseID() %>')">Add fact...</button>
					<%
				}
				%>
				<br/>
			</div>
		</div>
	</body>
</html>
