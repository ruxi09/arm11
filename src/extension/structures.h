//
// Created by Ruxi on 15/06/2020.
//

#ifndef CHAT_BOT_STRUCTURES_H
#define CHAT_BOT_STRUCTURES_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include <time.h>
#include <stdbool.h>

#define MAX_RESP 3

//maps each input to a possible response
typedef struct {
    char *input;
    char *responses[MAX_RESP];

} record;

//responses and inputs "database"
record KnowledgeBase[] = {
        {"WHAT IS YOUR NAME",
                {"MY NAME IS CHATTERBOT.",
                        "YOU CAN CALL ME CHATTERBOT.",
                        "WHY DO YOU WANT TO KNOW MY NAME?"}
        },

        {
         "MASTER",
                {
                 "AP1619, CT519, RF419, VN119",
                        "ANDREI, CRISTINA, RUXI, VLAD",
                        "AP1619, CT519, RF419, VN119"}
        },

        {
         "CREAT",
                {
                 "AP1619, CT519, RF419, VN119",
                        "ANDREI, CRISTINA, RUXI, VLAD",
                        "AP1619, CT519, RF419, VN119"}
        },

        {
         "WHO MADE YOU",
                {
                 "AP1619, CT519, RF419, VN119",
                        "ANDREI, CRISTINA, RUXI, VLAD",
                        "AP1619, CT519, RF419, VN119"}
        },

        {"LANGUAGE",
                {"C",
                        "MACHINE CODE",
                        "JUST ENGLISH, SORRY"}

        },

        {"HI",
                {"HI THERE!",
                        "HOW ARE YOU?",
                        "HI!"}
        },

        {"HOW ARE YOU",
                {"I AM DOING FINE!",
                        "I'M DOING WELL AND YOU?",
                        "WHY DO YOU WANT TO KNOW HOW AM I DOING?"}
        },

        {"WHO ARE YOU",
                {"I AM AN A.I. PROGRAM.",
                        "I THINK THAT YOU KNOW WHO I AM.",
                        "WHY ARE YOU ASKING?"}
        },

        {"YOU ARE VERY INTELLIGENT",
                {"THANKS FOR THE COMPLIMENT USER, I THINK THAT YOU ARE INTELLIGENT TOO!",
                        "YOU ARE A VERY GENTLE PERSON!",
                        "SO, YOU THINK THAT I'M INTELLIGENT."}
        },

        {"INTELLIGENT",
                {"YES,OF COURSE.",
                        "WHAT DO YOU THINK?",
                        "ACTUALLY,I'M VERY INTELLIGENT!"}
        },

        {"ARE YOU REAL",
                {"DOES THAT QUESTION REALLY MATTER TO YOU?",
                        "WHAT DO YOU MEAN BY THAT?",
                        "I'M AS REAL AS I CAN BE."}
        },

        {"ARE YOU A HUMAN BEING",
                {"WHY DO YOU WANT TO KNOW?",
                        "IS THIS REALLY RELEVANT?",
                        "JUST ON SPECIAL OCCASIONS"}
        },

        {"ARE YOU SURE",
                {"OF COURSE I AM.",
                        "IS THAT MEAN THAT YOU ARE NOT CONVINCED?",
                        "YES,OF COURSE!"}
        },

        {"WHO IS",
                {"I DONT THINK I KNOW.",
                        "DID YOU ASK SOMEONE ELSE ABOUT IT?",
                        "WOULD THAT CHANGE ANYTHING AT ALL IF I TOLD YOU."}
        },

        {"HOW OLD ARE YOU",
                {"WHY DO WANT TO KNOW MY AGE?",
                        "I'M QUIET YOUNG ACTUALLY.",
                        "SORRY, I CAN NOT TELL YOU MY AGE."}
        },

        {"HOW COME YOU DON'T",
                {"WERE YOU EXPECTING SOMETHING DIFFERENT?",
                        "ARE YOU DISAPPOINTED?",
                        "ARE YOU SURPRISED BY MY LAST RESPONSE?"}
        },

        {"WHERE ARE YOU FROM",
                {"I'M FROM A COMPUTER.",
                        "WHY DO YOU WANT TO KNOW WHERE I'M FROM?",
                        "WHY DO YOU WANT TO KNOW THAT?"}
        },

        {"DO YOU",
                {"I DONT THINK I DO",
                        "I WOULDN'T THINK SO.",
                        "WHY DO YOU WANT TO KNOW?"}
        },

        {"CAN YOU",
                {"I THINK NOT.",
                        "I'M NOT SURE.",
                        "I DONT THINK THAT I CAN DO THAT."}
        },

        {"YOU ARE",
                {"WHAT MAKES YOU THINK THAT?",
                        "IS THIS A COMPLIMENT?",
                        "ARE YOU MAKING FUN OF ME?"}
        },

        {"DID YOU",
                {"I DON'T THINK SO.",
                        "ANYWAY, I WOULDN'T REMEMBER EVEN IF I DID.",
                        "I CAN'T REMEMBER"}
        },

        {"COULD YOU",
                {"ARE YOU ASKING ME FOR A FEVER?",
                        "WELL, LET ME THINK ABOUT IT.",
                        "SORRY, I DON'T THINK THAT I COULD DO THIS."}
        },

        {"WOULD YOU",
                {"IS THAT AN INVITATION?",
                        "I WOULD HAVE TO THINK ABOUT IT FIRST.",
                        "NO!!"}
        },

        {"WHICH ONE",
                {"I DON'T THINK THAT I KNOW WHICH ONE IT IS.",
                        "THIS LOOKS LIKE A TRICKY QUESTION TO ME.",
                        "I AM NOT SURE"}
        },

        {"PERHAPS",
                {"WHY ARE YOU SO UNCERTAIN?",
                        "YOU SEEM UNCERTAIN.",
                        "MAYBE, WHY NOT"}
        },

        {"I DON'T KNOW",
                {"ARE YOU SURE?",
                        "ARE YOU REALLY TELLING ME THE TRUTH?",
                        "SO,YOU DON'T KNOW?"}
        },

        {"NOT REALLY",
                {"OK, I SEE.",
                        "YOU DON'T SEEM PRETTY CERTAIN.",
                        "SO,THAT WOULD BE A \"NO\"."}
        },

        {"IS THAT TRUE",
                {"I CAN'T BE QUITE SURE ABOUT THIS.",
                        "CAN'T TELL YOU FOR SURE.",
                        "DOES THAT REALLY MATTER TO YOU?"}
        },

        {"NO PROBLEM",
                {"SO, YOU APPROVE IT.",
                        "SO, IT'S ALL OK.",
                        "YAY"}
        },


        {"THANKS",
                {"YOU ARE WELCOME!",
                        "NO PROBLEM!",
                        "ANYTIME"}
        },

        {"WHAT ELSE",
                {"WELL, I DON'T KNOW.",
                        "WHAT ELSE SHOULD THERE BE?",
                        "THIS LOOKS LIKE A COMPLICATED QUESTION TO ME."}
        },

        {"YOU ARE WELCOME",
                {"OK, YOU TOO!",
                        "YOU ARE A VERY POLITE PERSON!",
                        "YOU ARE A GOOD FRIEND"}
        },

        {"SORRY",
                {"YOU DONT NEED TO BE SORRY USER.",
                        "IT'S OK.",
                        "NO NEED TO APOLOGIZE."}
        },

        {"NOT EXACTLY",
                {"WHAT DO YOU MEAN NOT EXACTLY?",
                        "ARE YOU SURE?",
                        "HMMM..."}
        },

        {"EXACTLY",
                {"SO, I WAS RIGHT.",
                        "OK THEN.",
                        "I'M A GENIUS!"}
        },

        {"ALRIGHT",
                {"ALRIGHT THEN.",
                        "OK THEN.",
                        "GREAT"}
        },

        {"I DON'T",
                {"WHY NOT?",
                        "AND WHAT WOULD BE THE REASON FOR THIS?",
                        "YOU BETTER DO"}
        },

        {"REALLY",
                {"WELL, I CAN'T TELL YOU FOR SURE.",
                        "ARE YOU TRYING TO CONFUSE ME?",
                        "PLEASE DON'T ASK ME SUCH QUESTIONS,IT GIVES ME HEADACHES."}
        },

        {"WHAT",
                {"I DON'T KNOW.",
                        "I DON'T THINK I KNOW.",
                        "I HAVE NO IDEA."}
        },

        {"WHERE",
                {"WHERE? WELL, I REALLY DON'T KNOW.",
                        "DOES THAT MATER TO YOU?",
                        "PERHAPS,SOMEONE ELSE KNOWS WHERE."}
        },

        {"WHY",
                {"I DON'T THINK I KNOW WHY.",
                        "WHY ARE YOU ASKING ME THIS?",
                        "SHOULD I KNOW WHY?"}
        },

        {"HOW",
                {"I DON'T THINK I KNOW HOW.",
                        "NOT MY PROBLEM",
                        "ASK SOMEONE ELSE"}
        },

        {"YOU",
                {"SO YOU ARE TALKING ABOUT ME.",
                        "WHY DON'T WE TALK ABOUT YOU INSTEAD?",
                        "ARE YOU TRYING TO MAKE FUN OF ME?"}
        },

        {"YES",
                {"SO,IT IS YES.",
                        "OH, REALLY?",
                        "OK THEN."}
        },

        {
         "NO",
                {"WHY NOT?",
                        "YOU CAN TRY",
                        "OK THEN"}
        }


};

int nKnowledgeBaseSize = sizeof(KnowledgeBase) / sizeof(KnowledgeBase[0]);

#endif //CHAT_BOT_STRUCTURES_H
