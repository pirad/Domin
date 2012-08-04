drop table if exists Card;

create table Card(
    id smallint primary key,
    name varchar(40), 
    descr varchar(500), 

    price smallint, 
    plus_actions smallint, 
    plus_money smallint, 
    plus_buys smallint, 
    plus_cards smallint,
    points smallint,
    money bool, 
    action bool, 
    attac bool, 
    reaction bool, 
    point bool, 
    curse bool, 
    
    game_base bool,
    game_intr bool,
    game_hinter bool,
    game_prosp bool,
    game_alch bool,
    game_sea bool,
    game_corn bool,
    game_misc bool
);

/* Geld */
insert into Card values (1, 'Kupfer', '', 0, 
    0, 1, 0, 0, 0, 
    1, 0, 0, 0, 0, 0, 
    1, 1, 0, 0, 0, 0, 0, 0);
insert into Card values (2, 'Silber', '', 3,
    0, 2, 0, 0, 0, 
    1, 0, 0, 0, 0, 0, 
    1, 1, 0, 0, 0, 0, 0, 0);
insert into Card values (3, 'Gold', '', 6, 
    0, 3, 0, 0, 0, 
    1, 0, 0, 0, 0, 0, 
    1, 1, 0, 0, 0, 0, 0, 0);

/* Punkte */
insert into Card values (4, 'Anwesen', '', 2, 
    0, 0, 0, 0, 1, 
    0, 0, 0, 0, 1, 0, 
    1, 1, 0, 0, 0, 0, 0, 0);
insert into Card values (5, 'Herzogtum', '', 5, 
    0, 0, 0, 0, 3, 
    0, 0, 0, 0, 1, 0, 
    1, 1, 0, 0, 0, 0, 0, 0);
insert into Card values (6, 'Provinz', '', 8, 
    0, 0, 0, 0, 6,
    0, 0, 0, 0, 1, 0, 
    1, 1, 0, 0, 0, 0, 0, 0);
insert into Card values (7, 'Fluch', '', 0, 
    0, 0, 0, 0, -1, 
    0, 0, 0, 0, 0, 1, 
    1, 1, 0, 0, 0, 0, 0, 0);

/* einfache Karten */
insert into Card values (8, 'Holzfäller', '', 3, 
    0, 2, 1, 0, 0, 
    0, 1, 0, 0, 0, 0, 
    1, 0, 0, 0, 0, 0, 0, 0);
insert into Card values (9, 'Dorf', '', 3, 
    2, 0, 0, 1, 0, 
    0, 1, 0, 0, 0, 0,
    1, 0, 0, 0, 0, 0, 0, 0);
insert into Card values (10, 'Schmiede', '', 4, 
    0, 0, 0, 3, 0, 
    0, 1, 0, 0, 0, 0, 
    1, 0, 0, 0, 0, 0, 0, 0);
insert into Card values (11, 'Markt', '', 5, 
    1, 1, 1, 1, 0, 
    0, 1, 0, 0, 0, 0, 
    1, 0, 0, 0, 0, 0, 0, 0);
insert into Card values (12, 'Jahrmarkt', '', 5, 
    2, 2, 1, 0, 0, 
    0, 1, 0, 0, 0, 0, 
    1, 0, 0, 0, 0, 0, 0, 0);/*überprüfen*/
insert into Card values (13, 'Laboratorium', '', 5, 
    1, 0, 0, 2, 0, 
    0, 1, 0, 0, 0, 0, 
    1, 0, 0, 0, 0, 0, 0, 0);
insert into Card values (14, 'Harem', '', 6, 
    0, 2, 0, 0, 2, 
    1, 0, 0, 0, 1, 0, 
    0, 1, 0, 0, 0, 0, 0, 0);
insert into Card values (15, 'Große Halle', '', 3,
    1, 0, 0, 1, 1, 
    0, 1, 0, 0, 1, 0, 
    0, 1, 0, 0, 0, 0, 0, 0);
insert into Card values (16, 'Kapelle', 'Entsorge bis zu 4 Karten aus deiner Hand.', 2,
    0, 0, 0, 0, 0, 
    0, 1, 0, 0, 0, 0, 
    1, 0, 0, 0, 0, 0, 0, 0);
