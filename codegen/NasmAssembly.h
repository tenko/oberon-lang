/*
 * Header of the NASM assembly produced code generator of the Oberon-0 compiler.
 *
 * Created by Michael Grossniklaus on 1/25/19.
 */

#ifndef OBERON0C_NASMASSEMBLY_H
#define OBERON0C_NASMASSEMBLY_H


#include <memory>
#include <ostream>
#include <vector>
#include "Section.h"

class NasmAssembly {

private:
    std::unique_ptr<Section> bss_;
    std::unique_ptr<Section> data_;
    std::unique_ptr<Section> text_;

public:
    explicit NasmAssembly();
    ~NasmAssembly() = default;

    Section* getBssSection() const;
    Section* getDataSection() const;
    Section* getTextSection() const;

    friend std::ostream& operator<<(std::ostream &stream, const NasmAssembly &node);

};

#endif //OBERON0C_NASMASSEMBLY_H
