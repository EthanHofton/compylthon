## Target Python CFG (Context Free Grammar)

$$
\begin{align}
\text{<program>}  & \to \text{<scope>}* \\

\text{<scope>}    & \to \{ \text{<statment>}* \} \\

\text{<statment>} & \to \text{<assignment>} \\
\text{<statment>} & \to \text{<conditional>} \\ 
\text{<statment>} & \to \text{<loop>} \\
\text{<statment>} & \to \text{<expression>} \\

\text{<conditional>} & \to \text{if} \ ( \text{<expression>} ) \ \text{<scope>} \ (\text{else} \ \text{<scope>})? \\

\text{<loop>} & \to \text{while} \ ( \text{<expression>} ) \ \text{<scope>} \\
\text{<loop>} & \to \text{for} (\text{<identifier>} \ \text{in} \ \text{<expression>}) \\

\text{<string\_literal>} & \to \text{"([\^ "\textbackslash \textbackslash]| \textbackslash \textbackslash .)*"} \\
\text{<number\_literal>}  & \to [0-9]+ \\
\text{<boolean\_literal>} & \to \text{true} \\
\text{<boolean\_literal>} & \to \text{false} \\

\text{<literal>} & \to \text{<string\_literal>} \\
\text{<literal>} & \to \text{<number\_literal>} \\
\text{<literal>} & \to \text{<boolean\_literal>} \\

\text{<identifier>} & \to \text{[a-zA-Z\_][a-zA-Z0-9\_]*} \\

\text{<expression>} & \to \text{<literal>} \\
\text{<expression>} & \to \text{<identifier>} \\
\text{<expression>} & \to \text{<binary\_expression>} \\
\text{<expression>} & \to \text{<unary\_expression>} \\
\text{<expression>} & \to (\text{<expression>}) \\
\text{<expression>} & \to \text{<function\_call>} \\

\text{<binary\_expression>} & \to \text{<expression>} \ \text{<binary\_operator>} \ \text{<expression>} \\
\text{<binary\_operator>} & \to + \\
\text{<binary\_operator>} & \to - \\
\text{<binary\_operator>} & \to * \\
\text{<binary\_operator>} & \to / \\
\text{<binary\_operator>} & \to ** \\

\text{<binary\_operator>} & \to == \\
\text{<binary\_operator>} & \to != \\
\text{<binary\_operator>} & \to <= \\
\text{<binary\_operator>} & \to >= \\
\text{<binary\_operator>} & \to > \\
\text{<binary\_operator>} & \to < \\
\text{<binary\_operator>} & \to \&\& \\
\text{<binary\_operator>} & \to || \\
\text{<binary\_operator>} & \to << \\
\text{<binary\_operator>} & \to >> \\
\text{<binary\_operator>} & \to \hat{} \\
\text{<binary\_operator>} & \to \& \\
\text{<binary\_operator>} & \to | \\

\text{<unary\_expression>} & \to \text{<unary\_operator>} \text{<expression>} \\
\text{<unary\_operator>} & \to ! \\

\text{<function\_call>} & \to \text{<identifier>} ( \text{<argument\_list>}) \\
\text{<argument\_list>} & \to \text{<expression>} \\
\text{<argument\_list>} & \to \text{<expression>}, \text{<argument\_list>} \\

\text{<assignment>} & \to \text{<identifier>} = \text{<expression>} \\

\end{align}
$$

## Current CFG

$$
$$
