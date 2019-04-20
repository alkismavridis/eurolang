#pragma once


class EulOperators {
    public: AssignOperator assignOperator;
    public: AssignModOperator assignModOperator;
    public: AssignXorOperator assignXorOperator;
    public: AssignAndOperator assignAndOperator;
    public: AssignStarOperator assignStarOperator;
    public: AssignMinusOperator assignMinusOperator;
    public: AssignPlusOperator assignPlusOperator;
    public: AssignOrOperator assignOrOperator;
    public: AssignDivOperator assignDivOperator;
    public: AssignLeftShiftOperator assignLeftShiftOperator;
    public: AssignRightShiftOperator assignRightShiftOperator;

    public: OrOperator orOperator;
    public: AndOperator andOperator;
    public: XorOperator xorOperator;
    public: NotEqualsOperator notEqualsOperator;
    public: NotSameOperator notSameOperator;
    public: EqualsOperator equalsOperator;
    public: SameOperator sameOperator;
    public: LessOperator lessOperator;
    public: LessEqualsOperator lessEqualsOperator;
    public: MoreOperator moreOperator;
    public: MoreEqualsOperator moreEqualsOperator;
    public: NotOperator notOperator;

    public: BinOrOperator binOrOperator;
    public: BinAndOperator binAndOperator;
    public: LeftShiftOperator leftShiftOperator;
    public: RightShiftOperator rightShiftOperator;
    public: PlusOperator plusOperator;
    public: MinusOperator minusOperator;
    public: PercentOperator percentOperator;
    public: StarOperator starOperator;
    public: SlashOperator slashOperator;
    public: TildeOperator tildeOperator;
    public: DecreaseOperator decreaseOperator;
    public: IncreaseOperator increaseOperator;
    public: DotOperator dotOperator;

    public: QuestionOperator questionOperator;
    public: ColonOperator colonOperator;
};


extern EulOperators EUL_OPERATORS;
