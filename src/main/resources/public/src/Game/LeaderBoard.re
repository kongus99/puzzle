let containerStyle = ReactDOMRe.Style.make(~width="100%", ());

type state =
  | Refreshing
  | Loaded(array(Score.score));

type action =
  | Refresh
  | UpdateLoaded(array(Score.score));

let reducer = (_, action) => {
  switch (action) {
  | Refresh => Refreshing
  | UpdateLoaded(scores) => Loaded(scores)
  };
};

[@react.component]
let make = (~refresh: bool) => {
  let (state, dispatch) = React.useReducer(reducer, Refreshing);

  React.useEffect1(
    () => {
      dispatch(Refresh);
      Score.fetch(s => dispatch(UpdateLoaded(s)));
      None;
    },
    [|refresh|],
  );

  switch (state) {
  | Refreshing => ReasonReact.string("Loading...")
  | Loaded(scores) =>
    <table style=containerStyle>
      <tr>
        <th> {React.string("Name")} </th>
        <th> {React.string("Result")} </th>
      </tr>
      {Score.(
         scores
         |> Array.map(s =>
              <tr>
                <td> {React.string(s.name)} </td>
                <td> {s.result |> string_of_int |> React.string} </td>
              </tr>
            )
         |> React.array
       )}
    </table>
  };
};
