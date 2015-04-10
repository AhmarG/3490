(*
   Quilts an implementation of Chapter 4 case study

   Skeleton code (incl. Graphics module) provided by Dr. Fenwick
   Sewing module implemented by: 
*)

module JQuilts

    (* Let's define a "type Texture" to be a union of Arcs or Bands,
       and a "type Direction" to a union of NE, SE, SW, NW
    *)
    type Texture =  | Arcs
                    | Bands
    type Direction = | NE
                     | SE
                     | SW
                     | NW

    (* Let's define the two starting squares for anyone to use! *)
    let arcsNE = [[(Arcs, NE)]]
    let bandsNE = [[(Bands, NE)]];;


    (*************************************************************
     *******         S E W I N G           M O D U L E   *********
     *******                                             *********
     *******   Student writes all the sewing functions.  *********
     ************************************************************)
    module Sewing =

       let rec isEmpty quilt =
        match quilt with
        | [] -> true
        | []::tl -> isEmpty tl
        | hd::tl -> false

       let rec sew quilt1 quilt2 =
        if isEmpty quilt1 && isEmpty quilt2 then []
        else
            let h1 = List.head quilt1
            let h2 = List.head quilt2
            let t1 = List.tail quilt1
            let t2 = List.tail quilt2
            (h1 @ h2)::(sew t1 t2)

       let clockwise dir =
        match dir with
        | NE->SE
        | SE->SW
        | SW->NW
        | NW->NE

       let turnSquare sq =
        let txt = fst sq
        let dir = snd sq
        let dir2 = clockwise dir
        (txt, dir2)

       let rec turn quilt =
        if isEmpty quilt then []
        else
            let col = (List.map List.head quilt)
            let row = (List.rev col)
            (List.map turnSquare row)::turn (List.map List.tail quilt)

       let unturn quilt = turn (turn (turn quilt))

       (* Do this like it would be sewn, so can only use sewing functions
          like sew, pile, turn, etc. *)
       let rec pile quilt1 quilt2 = unturn (sew (turn quilt1) (turn quilt2))

       (* An efficient one-statement way to combine the lists of tuples
          to achieve a pile. *)
       let rec effpile quilt1 quilt2 = quilt1 @ quilt2



    (*************************************************************
     *******         G R A P H I C S       M O D U L E   *********
     *******                                             *********
     *******    does all the bitmap-y image stuff.       *********
     ************************************************************)
    module Graphics =
       open System.Drawing

       let encodeImage square =
          match square with
          | Bands,NE ->  new Bitmap("bandsNE.JPG");
          | Bands,SE ->  new Bitmap("bandsSE.JPG");
          | Bands,SW ->  new Bitmap("bandsSW.JPG");
          | Bands,NW ->  new Bitmap("bandsNW.JPG");
          | Arcs,NE -> new Bitmap("arcsNE.JPG");
          | Arcs,SE -> new Bitmap("arcsSE.JPG");
          | Arcs,SW -> new Bitmap("arcsSW.JPG");
          | Arcs,NW -> new Bitmap("arcsNW.JPG");

       let stitchRowImage r = List.map encodeImage r

       let rec calcWidth (r : List<Bitmap>) width =
          match r with
          | [] -> width
          | hd::td -> let r = calcWidth td width
                      hd.Width + r

       let rec calcHeight x =
          match x with
          | [] -> 0
          | hd::td -> 80 + calcHeight td

       let calcRowWidth r = calcWidth r 0

       let saveFinalImage (bitmaps : List<List<Bitmap>>)
                       (final : Bitmap) (fileName: string) =
          let g = Graphics.FromImage(final)
          let mutable widthOffset = 0
          let mutable heightOffset = 0
          for row in bitmaps do
             widthOffset <- 0
             for b in row do
                g.DrawImage(b, new Rectangle(widthOffset, heightOffset, 80, 80))
                widthOffset <- widthOffset + 80;
             heightOffset <- heightOffset + 80
          final.Save(fileName, System.Drawing.Imaging.ImageFormat.Jpeg);

       let createQuiltImage quilt file =
          let bitmaps = List.map stitchRowImage quilt
          let width = calcRowWidth (List.head bitmaps)
          let height = calcHeight bitmaps
          let final = new Bitmap(width, height)
          saveFinalImage bitmaps final file
          ()



    (*************************************************************
     *******         T E S T I N G         M O D U L E   *********
     *******                                             *********
     *******    Puts it all together!                    *********
     ************************************************************)
    module Testing =
       open Sewing
       open Graphics

       (* Example testing as shown in textbook *)
       let slice =
          let aa = pile (unturn arcsNE) (turn arcsNE)
          let bb = pile bandsNE (turn (turn bandsNE))
          let q = sew aa bb
          pile q q
       let page47quilt = sew slice (sew slice slice)

       let makePage47quilt =
          createQuiltImage  page47quilt "p47quilt.jpg";;



       (* Student testing code to make a 2x12 "runner" quilt, save
          in "runner.jpg" file. *)

       open Sewing
       open Graphics

       let runner =
          let row = sew arcsNE bandsNE
          let col = pile row row
          let coll = pile col col
          pile coll (pile coll coll);;

       let makeRunner = createQuiltImage  runner "runner.jpg";;



       (* Student testing code to make a 30 square quilt, save
          in "squares30.jpg" file. *)

       open Sewing
       open Graphics

       let sq30 =
        let row = sew arcsNE bandsNE
        let row2 = sew row row
        let row3 = sew row2 row
        let col = pile row3 row3
        let col2 = pile col col
        pile col2 row3

       let make30 = createQuiltImage sq30 "squares30.jpg";;
