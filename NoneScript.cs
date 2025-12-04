namespace NoneScript
{
  public enum TokenType
  {
    Let,
    Identifier,
    Equals,
    Number,
    OpenParentese, CloseParentese,
    BinaryOperator
  }
  public struct Token
  {
    string value;
    TokenType type;
  }
  public class NoneLexer
  {
    public static Token[] Tokenize(string sourceCode)
    {
      Token[] tokens = [];

      return tokens;
    }
  }
}
