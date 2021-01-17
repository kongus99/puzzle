type state = {
  user: option(string),
  refresh: bool,
};

type action =
  | SubmitUser(string)
  | RefreshBoard;

let initialState = {user: None, refresh: false};

let reducer = (state, action) => {
  switch (action) {
  | SubmitUser(u) =>
    if (String.trim(u) |> String.length > 0) {
      {...state, user: Some(String.trim(u))};
    } else {
      {...state, user: None};
    }
  | RefreshBoard => {...state, refresh: !state.refresh}
  };
};

[@react.component]
let make = () => {
  let (state, dispatch) = React.useReducer(reducer, initialState);
  <div>
    <Container title="Puzzle Game">
      {switch (state.user) {
       | None => <Intro onSubmit={v => dispatch(SubmitUser(v))} />
       | Some(u) => <Game user=u onFinish={_ => dispatch(RefreshBoard)} />
       }}
    </Container>
    <Container title="Leader Board">
      <LeaderBoard refresh={state.refresh} />
    </Container>
  </div>;
};
