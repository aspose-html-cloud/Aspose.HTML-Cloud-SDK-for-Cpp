/**
* --------------------------------------------------------------------------------------------------------------------
* <copyright company="Aspose" file="PdfMetadata.cpp">
*  Copyright (c) 2022 Aspose.HTML for Cloud
* </copyright>
* <summary>
*  Permission is hereby granted, free of charge, to any person obtaining a copy
*  of this software and associated documentation files (the "Software"), to deal
*  in the Software without restriction, including without limitation the rights
*  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
*  copies of the Software, and to permit persons to whom the Software is
*  furnished to do so, subject to the following conditions:
*
*  The above copyright notice and this permission notice shall be included in all
*  copies or substantial portions of the Software.
*
*  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
*  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
*  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
*  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
*  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
*  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
*  SOFTWARE.
* </summary>
* --------------------------------------------------------------------------------------------------------------------
*/

#include "model/PdfMetadata.h"

namespace com {
namespace aspose {
namespace model {

PdfMetadata::PdfMetadata() {}
PdfMetadata::~PdfMetadata() {}

void PdfMetadata::validate() {}

web::json::value PdfMetadata::toJson() const
{
    web::json::value val = web::json::value::object();

    if (m_title)
    {
        val[utility::conversions::to_string_t("title")] = ModelBase::toJson(*m_title);
    }
    if (m_author)
    {
        val[utility::conversions::to_string_t("author")] = ModelBase::toJson(*m_author);
    }
    if (m_subject)
    {
        val[utility::conversions::to_string_t("subject")] = ModelBase::toJson(*m_subject);
    }
    if (m_keywords)
    {
        val[utility::conversions::to_string_t("keywords")] = ModelBase::toJson(*m_keywords);
    }
    if (m_creator)
    {
        val[utility::conversions::to_string_t("creator")] = ModelBase::toJson(*m_creator);
    }
    if (m_producer)
    {
        val[utility::conversions::to_string_t("producer")] = ModelBase::toJson(*m_producer);
    }
    if (m_creationDate)
    {
        val[utility::conversions::to_string_t("creationDate")] = ModelBase::toJson(*m_creationDate);
    }
    if (m_modificationDate)
    {
        val[utility::conversions::to_string_t("modificationDate")] = ModelBase::toJson(*m_modificationDate);
    }
    return val;
}

void PdfMetadata::fromJson(web::json::value& json) {}

std::string PdfMetadata::toString() const
{
    auto val = toJson().serialize();
    return utility::conversions::to_utf8string(val);
}

void PdfMetadata::toMultipart(std::shared_ptr<MultipartFormData> multipart, const utility::string_t& prefix) const {}
void PdfMetadata::fromMultiPart(std::shared_ptr<MultipartFormData> multipart, const utility::string_t& prefix) {}

PdfMetadata* PdfMetadata::setTitle(const utility::string_t& value)
{
    m_title = value;
    return this;
}

PdfMetadata* PdfMetadata::setAuthor(const utility::string_t& value)
{
    m_author = value;
    return this;
}

PdfMetadata* PdfMetadata::setSubject(const utility::string_t& value)
{
    m_subject = value;
    return this;
}

PdfMetadata* PdfMetadata::setKeywords(const utility::string_t& value)
{
    m_keywords = value;
    return this;
}

PdfMetadata* PdfMetadata::setCreator(const utility::string_t& value)
{
    m_creator = value;
    return this;
}

PdfMetadata* PdfMetadata::setProducer(const utility::string_t& value)
{
    m_producer = value;
    return this;
}

PdfMetadata* PdfMetadata::setCreationDate(const utility::string_t& value)
{
    m_creationDate = value;
    return this;
}

PdfMetadata* PdfMetadata::setModificationDate(const utility::string_t& value)
{
    m_modificationDate = value;
    return this;
}

}
}
}
