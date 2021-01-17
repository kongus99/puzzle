type score = {
  name: string,
  result: int,
};

module Encode = {
  let score: score => Js.Json.t =
    score =>
      Json.Encode.(
        object_([
          ("name", string(score.name)),
          ("result", int(score.result)),
        ])
      );
};

module Decode = {
  let score = json =>
    Json.Decode.{
      name: json |> field("name", string),
      result: json |> field("result", int),
    };
};

let fetch = onSuccess =>
  Fetcher.get(
    "/api/leaderboard",
    [],
    Fetcher.statusResolver([||], _ => (), Fetch.Response.json),
    json =>
    onSuccess(json |> Json.Decode.array(Decode.score))
  );

let post = (score, onSuccess) =>
  Fetcher.post(
    "/api/leaderboard",
    Encode.score(score),
    Fetcher.statusResolver([||], _ => (), Fetch.Response.json),
    json =>
    onSuccess(json |> Decode.score)
  );
