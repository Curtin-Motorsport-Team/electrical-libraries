README
======

A general repository to keep track of the various libraries CMT use in
their electrical projects.


Documentation
-------------

### Building ###

To automatically generate the documentation, use:

    make docs

The documentation will then be placed in the `docs` directory. If your
point your browser at the documentation home page (`docs/html/index.html`),
you'll be able to explore the entire repository. You can explore the
file tree to find the signatures and documentation for pretty much
everything.

(Note: You need to have [Doxygen][doxygen] installed to build docs)


### Writing ###

If you want `Doxygen` to automatically generate documentation from your
source files, you need to format your comments slightly differently.

Often this is just a case of adding a `!` after the `/*` or `//`
when you write a comment.


    //!  A test class.
    /*!
     *  A more elaborate class description.
     */
    class QTstyle_Test
    {
    public:
        //! An enum.
        /*! More detailed enum description. */
        enum TEnum {
                    TVal1, /*!< Enum value TVal1. */
                    TVal2, /*!< Enum value TVal2. */
                    TVal3  /*!< Enum value TVal3. */
                }
            //! Enum pointer.
            /*! Details. */
            *enumPtr,
            //! Enum variable.
            /*! Details. */
            enumVar;

        //! A constructor.
        /*!
         * A more elaborate description of the constructor.
         */
        QTstyle_Test();
        //! A destructor.
        /*!
         * A more elaborate description of the destructor.
         */
    ~QTstyle_Test();

        //! A normal member taking two arguments and returning an integer value.
        /*!
         * \param a an integer argument.
         * \param s a constant character pointer.
         * \return The test results
         * \sa QTstyle_Test(), ~QTstyle_Test(), testMeToo() and publicVar()
         */
        int testMe(int a,const char *s);

        //! A pure virtual member.
        /*!
         * \sa testMe()
         * \param c1 the first argument.
         * \param c2 the second argument.
         */
        virtual void testMeToo(char c1,char c2) = 0;

        //! A public variable.
        /*!
         * Details.
         */
        int publicVar;

        //! A function variable.
        /*!
         * Details.
         */
        int (*handler)(int a,int b);
    };


Contributing
------------

To make any changes to this repository, first create your own fork (using
the `Fork` button in the top left when you look at the repo on GitHub), make
your changes, then send a pull request so the changes can be merged back into
the main repository.

For more information on GitHub's [Fork and Pull Request][fork-pull-request]
model check the docs.



[doxygen]: http://www.stack.nl/~dimitri/doxygen/download.html
[fork-pull-request]: https://help.github.com/articles/about-pull-requests/
